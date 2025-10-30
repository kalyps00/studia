#include "arithmetic.hpp"

#include <array>
#include <cstdint>
#include <limits>
#include <tuple>
#include <iostream>
// The following implementation is based on:
//
// Mark Nelson's "Data Compression With Arithmetic Coding" article
// https://web.archive.org/web/20241217122540/https://marknelson.us/posts/2014/10/19/data-compression-with-arithmetic-coding.html
//
// and
//
// mathematicalmonk's "Information Theory" YouTube series
// https://www.youtube.com/watch?v=ouYV3rBtrTI&list=PLE125425EC837021F&index=41

namespace {
// Type used to store a single code
typedef std::uint64_t code_t;

// Number of bits available to represent numbers
const std::size_t PRECISION = std::numeric_limits<code_t>::digits;

// 256 possible char values and the EOF code
const std::size_t ALPHABET_LEN = 257;
// The code used to indicate EOF
const code_t CODE_EOF = ALPHABET_LEN - 1;

// Bits available for code value
const std::size_t CODE_VALUE_BITS = PRECISION / 2 + 1;
// Maximum code value
const code_t MAX_CODE = (code_t(1) << CODE_VALUE_BITS) - 1;

// Bits available for frequency
const std::size_t FREQUENCY_BITS = PRECISION - CODE_VALUE_BITS;
// Maximum frequency
const code_t MAX_FREQUENCY = (code_t(1) << FREQUENCY_BITS) - 1;

// The values representing: 0.25, 0.5, 0.75, 1.0
const code_t QUARTER1 = code_t(1) << (CODE_VALUE_BITS - 2);
const code_t QUARTER2 = 2 * QUARTER1;
const code_t QUARTER3 = 3 * QUARTER1;

struct Probability {
    code_t low;
    code_t high;
    code_t count;
};

struct Range {
    code_t left;
    code_t right;

    Range() : left(0), right(MAX_CODE) {}

    void update(Probability prob) {
        auto width = right - left + 1;
        right = left + (width * prob.high / prob.count) - 1;
        left = left + (width * prob.low / prob.count);
    }

    void decrease(code_t delta) {
        left -= delta;
        right -= delta;
    }
};

class Model {
    // Freez the model once the total frequency reaches MAX_FREQUENCY
    bool frozen;
    // The cumulative frequencies of each alphabet letter
    // One more space needed, because there is also a sum of all frequencies
    std::array<code_t, ALPHABET_LEN + 1> cumulative;

  public:
    Model() : frozen(false) {
        for (code_t i = 0; i < cumulative.size(); i++) {
            cumulative[i] = i;
        }
    }

    Probability get_probability(std::uint16_t ch) {
        Probability p = {cumulative[ch], cumulative[ch + 1], cumulative.back()};
        update(ch);
        return p;
    }

    void update(std::uint16_t ch) {
        if (frozen) {
            return;
        }

        for (code_t i = ch + 1; i < cumulative.size(); i++) {
            cumulative[i]++;
        }

        if (cumulative.back() == MAX_FREQUENCY) {
            frozen = true;
        }
    }

    code_t get_count() { return cumulative.back(); }

    std::tuple<Probability, code_t> get_char(code_t value) {
        std::uint16_t left = 0;
        std::uint16_t right = CODE_EOF;
        std::uint16_t mid = 0;

        while (left <= right) {
            mid = left + (right - left) / 2;

            // Found the right range
            if (cumulative[mid] <= value && cumulative[mid + 1] > value) {
                break;
            }

            // Overstepped by one range
            if (cumulative[mid] > value && cumulative[mid + 1] <= value) {
                mid--;
                break;
            }

            if (cumulative[mid] > value) { // Check left half
                right = mid - 1;
            } else { // Check right half
                left = mid + 1;
            }
        }

        return {get_probability(mid), mid};
    }
};

class Compressor {
    code_t pending;
    Range range;
    Model model;
    bitio::bit_ostream &output;

  public:
    Compressor(bitio::bit_ostream &output) : pending(0), output(output) {}

    void emit(bool bit) {
        output.put_bit(bit);
        for (size_t i = 0; i < pending; i++) {
            output.put_bit(!bit);
        }
        pending = 0;
    }

    void compress(std::istream &input) {
        std::uint16_t ch = 0;

        while (ch != CODE_EOF) {
            ch = input.get();
            if (input.eof()) {
                ch = CODE_EOF;
            }

            auto prob = model.get_probability(ch);
            range.update(prob);

            // The range width is less than 0.5 and both ends of the range have
            // the same most significant bit - emit the known bit and reduce the
            // range
            while (range.left >= QUARTER2 || range.right < QUARTER2) {
                emit(range.left >= QUARTER2);
                range.left = (range.left << 1) & MAX_CODE;
                range.right = ((range.right << 1) + 1) & MAX_CODE;
            }

            // The range width is less than 0.5, but the ends of the range have
            // different most significant bits - remeber to output a bit later
            // and reduce the range
            while (range.left >= QUARTER1 && range.right < QUARTER3) {
                pending++;
                range.decrease(QUARTER1);
                range.left <<= 1;
                range.right = (range.right << 1) + 1;
            }
        }

        // Emit the remaing bits
        pending++;
        emit(range.left >= QUARTER1);

        output.flush();
    }
};

class Decompressor {
    code_t current;
    Range range;
    Model model;
    std::ostream &output;

  public:
    Decompressor(std::ostream &output) : current(0), range(), output(output) {}

    void decompress(bitio::bit_istream &input) {
        for (size_t i = 0; i < CODE_VALUE_BITS; i++) {
            current = (current << 1) | input.get_bit();
        }

        while (true) {
            auto width = range.right - range.left + 1;
            auto scaled_current =
                ((current - range.left + 1) * model.get_count() - 1) / width;
            auto [prob, ch] = model.get_char(scaled_current);

            if (ch == CODE_EOF) {
                break;
            }

            output.put(ch);
            range.update(prob);

            // The range width is less than 0.5 and both ends are in the same
            // half - scale up the range
            while (range.left >= QUARTER2 || range.right < QUARTER2) {
                if (range.left >= QUARTER2) {
                    range.decrease(QUARTER2);
                    current -= QUARTER2;
                }

                range.left <<= 1;
                range.right = (range.right << 1) + 1;
                current = (current << 1) | input.get_bit();
            }

            // The range width is less than 0.5, and both ends are in the 0.25
            // to 0.75 range - scale up the range
            while (range.left >= QUARTER1 && range.right < QUARTER3) {
                range.decrease(QUARTER1);
                range.left <<= 1;
                range.right = (range.right << 1) + 1;
                current = ((current - QUARTER1) << 1) | input.get_bit();
            }
        }
    }
};
} // namespace

namespace bitio {
/******************************* INPUT STREAM *******************************/

/*                             BASE INPUT STREAM                            */

bit_istream::bit_istream() : buf(0), mask(0) {}

bool bit_istream::get_bit() {
    if (mask == 0b0) {
        mask = 0b10000000;
        buf = get_char();
    }

    bool result = (buf & mask) != 0;
    mask >>= 1;
    return result;
};

bool bit_istream::eof() const { return mask == 0 && stream_eof(); }

/*                             FILE INPUT STREAM                            */

bit_ifstream::bit_ifstream(const std::string &filename)
    : std::ifstream(filename, std::ios::binary) {}

char bit_ifstream::get_char() { return std::ifstream::get(); }

bool bit_ifstream::stream_eof() const { return std::ifstream::eof(); }

/*                            STRING INPUT STREAM                           */

bit_string_istream::bit_string_istream(const std::string_view input)
    : iter(input.begin()), end(input.end()) {}

char bit_string_istream::get_char() { return *(iter++); }

bool bit_string_istream::stream_eof() const { return iter == end; }

/****************************** OUTPUT  STREAM ******************************/

/*                            BASE OUTPUT STREAM                            */

bit_ostream::bit_ostream() : buf(0), count(0) {}

void bit_ostream::fill() {
    if (count == 0) {
        return;
    }

    buf <<= 8 - count;
    put_char(buf);
}

void bit_ostream::put_bit(bool bit) {
    buf = (buf << 1) | bit;
    count++;

    if (count == 8) {
        put_char(buf);
        buf = 0;
        count = 0;
    }
};

/*                            FILE OUTPUT STREAM                            */

bit_ofstream::bit_ofstream(const std::string &filename)
    : std::ofstream(filename, std::ios::binary) {}

void bit_ofstream::put_char(std::uint8_t ch) { std::ofstream::put(ch); }

void bit_ofstream::flush() {
    bit_ostream::fill();
    std::ofstream::flush();
}

void bit_ofstream::close() { std::ofstream::close(); }

/*                           STRING OUTPUT STREAM                           */

bit_string_ostream::bit_string_ostream() {}

void bit_string_ostream::put_char(std::uint8_t ch) { output.push_back(ch); }

void bit_string_ostream::flush() { bit_ostream::fill(); }

std::string bit_string_ostream::result() { return output; }
} // namespace bitio

namespace arithmetic {
void compress(std::istream &input, bitio::bit_ostream &output) {
    Compressor(output).compress(input);
}

void decompress(bitio::bit_istream &input, std::ostream &output) {
    Decompressor(output).decompress(input);
}
} // namespace arithmetic



extern "C"{
  void  c_compress(char* file_in,char* file_out){
    auto input_path = std::string(file_in);
    auto input_stream = std::ifstream(input_path);
    if (!input_stream.is_open()) {
        std::cerr << "Error: cannot open given file: " << input_path << "\n";
        return;
    }
    
    std::string compressed_path = std::string(file_out);
    std::cout << "Compressing to '" << compressed_path << "' ...";
    bitio::bit_ofstream compressed_stream(compressed_path);
    arithmetic::compress(input_stream, compressed_stream);
    std::cout << " Done." << std::endl;
    return;

  }
  void  c_decompress(char* file_in,char* file_out){
    auto input_path = std::string(file_in);
    auto input_stream = bitio::bit_ifstream(input_path);
   
    
    std::string compressed_path = std::string(file_out);
    std::cout << "Decompressing to '" << compressed_path << "' ...";
    std::ofstream compressed_stream(compressed_path);
    arithmetic::decompress(input_stream, compressed_stream);
    std::cout << " Done." << std::endl;
    return;
  }
 
}
