#include "base64.hpp"

#include <cstdint>
#include <limits>

namespace {
struct Specification {
    const std::string_view alphabet;
    const char padding;
    const size_t line_len;
    const std::string_view line_separator;
    const bool discard_nonecoding_characters;
};

const Specification RFC1421 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    64,
    "\r\n",
    false,
};

const Specification RFC2045 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    76,
    "\r\n",
    true,
};

const Specification RFC2152 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '\0',
    0,
    "",
    false,
};

const Specification RFC3501 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+,",
    '\0',
    0,
    "",
    false,
};

const Specification RFC4648_4 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    0,
    "",
    false,
};

const Specification RFC4648_5 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_",
    '=',
    0,
    "",
    false,
};

const Specification RFC4880 = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
    '=',
    76,
    "\r\n",
    false,
};

class Encoder {
    const Specification &spec;
    std::string buf;

  public:
    Encoder(const Specification &spec) : spec(spec) {}

    void append_char(char ch) {
        buf += ch;
        if (spec.line_len != 0 && buf.length() % spec.line_len == 0) {
            buf += spec.line_separator;
        }
    }

    void append(size_t index) { this->append_char(spec.alphabet[index]); }

    std::string encode(const std::string_view input) {
        buf.clear();
        buf.reserve(input.length() / 3 * 4);

        std::uint8_t reminder = 0;
        std::uint8_t chunk_len = 6;
        std::uint8_t mask = 0b11;

        for (const auto ch : input) {
            if (chunk_len == 0) {
                this->append(reminder);
                reminder = 0;
                chunk_len = 6;
                mask = 0b11;
            }

            this->append((reminder << chunk_len) | (ch >> (8 - chunk_len)));

            reminder = ch & mask;
            chunk_len -= 2;
            mask = (mask << 2) | 0b11;
        }

        if (chunk_len != 6) {
            this->append(reminder << chunk_len);
        }

        for (size_t i = 0; i < this->buf.length() % 4; i++) {
            this->append_char(spec.padding);
        }

        return this->buf;
    }
};

class Decoder {
    const Specification &spec;
    std::uint8_t map[std::numeric_limits<uint8_t>::max()];
    std::string buf;

  public:
    Decoder(const Specification &spec) : spec(spec) {
        for (size_t i = 0; i < std::numeric_limits<uint8_t>::max(); i++) {
            map[i] = std::numeric_limits<uint8_t>::max();
        }

        for (size_t i = 0; i < spec.alphabet.length(); i++) {
            map[(size_t)spec.alphabet[i]] = i;
        }
    }

    std::optional<std::string> decode(const std::string_view input) {
        this->buf.clear();
        buf.reserve(input.length() / 4 * 3);

        std::uint8_t buffer = 0;
        std::uint8_t chunk_len = 0;

        for (const auto ch : input) {
            if (spec.line_separator.find(ch) != std::string_view::npos) {
                continue;
            } else if (ch == spec.padding) {
                break;
            }

            std::uint8_t val = map[(size_t)ch];

            if (val == std::numeric_limits<uint8_t>::max()) {
                if (spec.discard_nonecoding_characters) {
                    continue;
                } else {
                    return {};
                }
            }

            if (chunk_len == 0) {
                chunk_len = 8;
            } else {
                buffer |= val >> (chunk_len - 2);
                buf += buffer;
            }

            buffer = (val << (10 - chunk_len)) & 0b11111111;
            chunk_len -= 2;
        }

        return this->buf;
    }
};
} // namespace

namespace base64 {
std::string encode1421(const std::string_view input) {
    return Encoder(RFC1421).encode(input);
}

std::optional<std::string> decode1421(const std::string_view input) {
    return Decoder(RFC1421).decode(input);
}

std::string encode2045(const std::string_view input) {
    return Encoder(RFC2045).encode(input);
}

std::optional<std::string> decode2045(const std::string_view input) {
    return Decoder(RFC2045).decode(input);
}

std::string encode2152(const std::string_view input) {
    return Encoder(RFC2152).encode(input);
}

std::optional<std::string> decode2152(const std::string_view input) {
    return Decoder(RFC2152).decode(input);
}

std::string encode3501(const std::string_view input) {
    return Encoder(RFC3501).encode(input);
}

std::optional<std::string> decode3501(const std::string_view input) {
    return Decoder(RFC3501).decode(input);
}

std::string encode4648_4(const std::string_view input) {
    return Encoder(RFC4648_4).encode(input);
}

std::optional<std::string> decode4648_4(const std::string_view input) {
    return Decoder(RFC4648_4).decode(input);
}

std::string encode4648_5(const std::string_view input) {
    return Encoder(RFC4648_5).encode(input);
}

std::optional<std::string> decode4648_5(const std::string_view input) {
    return Decoder(RFC4648_5).decode(input);
}

std::string encode4880(const std::string_view input) {
    return Encoder(RFC4880).encode(input);
}

std::optional<std::string> decode4880(const std::string_view input) {
    return Decoder(RFC4880).decode(input);
}
} // namespace base64
