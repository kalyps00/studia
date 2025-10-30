#include <cstdint>
#include <fstream>
#include <string>
#include <string_view>

namespace bitio {
/******************************* INPUT STREAM *******************************/

/// @brief A base class for bit wise input stream
class bit_istream {
    std::uint8_t buf;
    std::uint8_t mask;

    /// @brief Returns a whole byte from the stream
    ///
    /// Used internally by `bit_istream::get_bit()`
    virtual char get_char() = 0;

    /// @brief Returns wether the stream reach eof
    ///
    /// Used internally by `bit_istream::eof()`
    virtual bool stream_eof() const = 0;

  public:
    bit_istream();

    /// @brief Returns next bit (undefined if stream reached eof)
    bool get_bit();

    /// @brief Returns wether all bits from the stream were read
    bool eof() const;
};

/// @brief A class for bit wise input stream using an ifstream
class bit_ifstream : std::ifstream, public bit_istream {
    char get_char() override;
    bool stream_eof() const override;

  public:
    bit_ifstream(const std::string &filename);
};

/// @brief A class for bit wise input stream using a string
class bit_string_istream : public bit_istream {
    std::string_view::const_iterator iter;
    std::string_view::const_iterator end;

    char get_char() override;
    bool stream_eof() const override;

  public:
    bit_string_istream(const std::string_view input);
};

/****************************** OUTPUT  STREAM ******************************/

/// @brief A base class for bit wise output stream
class bit_ostream {
    std::uint8_t buf;
    std::uint8_t count;

    /// @brief Puts a whole byte into the stream
    ///
    /// Used internally by `bit_ostream::put_bit()`
    virtual void put_char(std::uint8_t) = 0;

  protected:
    /// @brief Fills the pending byte with zeros
    ///
    /// Must be called from `bit_ostream::flush()`
    void fill();

  public:
    bit_ostream();

    /// @brief Puts a single bit into the stream
    void put_bit(bool bit);

    /// @brief Flushes the stream
    ///
    /// Must call `bit_ostream::fill()`
    virtual void flush() = 0;
};

/// @brief A class for bit wise output stream using an ofstream
class bit_ofstream : std::ofstream, public bit_ostream {
    void put_char(std::uint8_t ch) override;

  public:
    bit_ofstream(const std::string &filename);
    void flush() override;

    /// @brief Closes the underlying ofstream
    void close();
};

/// @brief A class for bit wise output stream using a string
class bit_string_ostream : public bit_ostream {
    std::string output;
    void put_char(std::uint8_t ch) override;

  public:
    bit_string_ostream();
    void flush() override;

    /// @brief Returns the underlying string
    std::string result();
};
} // namespace bitio

namespace arithmetic {
/// @brief Adaptive arithmetic coding compressor
///
/// @paramin input (byte wise) stream to be compress
/// @paramin output (bit wise) stream for the compressed data
void compress(std::istream &input, bitio::bit_ostream &output);

/// @brief Adaptive arithmetic coding decompressor
///
/// @paramin input (bit wise) stream to be decompress
/// @paramin output (byte wise) stream for the decompressed data
void decompress(bitio::bit_istream &input, std::ostream &output);
} // namespace arithmetic

extern "C"{
  void c_compress(char* file_in,char* file_out);
  void c_decompress(char* file_in,char* file_out);
}
