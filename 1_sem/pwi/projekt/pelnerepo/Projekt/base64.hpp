#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace base64 {

/// @brief Base64 encoding using RFC 1421 (Privacy-Enhanced Mail) specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is padded to multiple of 4 bytes with `=` (mandatory)
/// Lines are at most 64 bytes long and separated with `CR+LF` (`\r\n`)
///
/// This was the first known standardized base64 encoding, but is now
/// deprecated in favor of RFC 2045 (MIME).
std::string encode1421(const std::string_view input);

/// @brief Base64 decoding using RFC 1421 (Privacy-Enhanced Mail) specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is padded to multiple of 4 bytes with `=` (mandatory)
/// Lines are at most 64 bytes long and separated with `CR+LF`
///
/// This was the first known standardized base64 encoding, but is now
/// deprecated in favor of RFC 2045 (MIME).
std::optional<std::string> decode1421(const std::string_view input);

/// @brief Base64 encoding using RFC 2045 (MIME) specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is padded to multiple of 4 bytes with `=` (mandatory)
/// Lines are at most 76 bytes long and separated with `CR+LF` (`\r\n`)
std::string encode2045(const std::string_view input);

/// @brief Base64 decoding using RFC 2045 (MIME) specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is padded to multiple of 4 bytes with `=` (mandatory)
/// Lines are at most 76 bytes long and separated with `CR+LF` (`\r\n`)
/// Discards non-encoding characters
std::optional<std::string> decode2045(const std::string_view input);

/// @brief Base64 encoding using RFC 2152 (UTF-7) specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is is not padded
/// Lines are not separated
std::string encode2152(const std::string_view input);

/// @brief Base64 decoding using RFC 2152 (UTF-7) specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is is not padded
/// Lines are not separated
std::optional<std::string> decode2152(const std::string_view input);

/// @brief Base64 encoding using RFC 3501 (IMAP mailbox names) specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `+` as 62nd and `,` as 63rd characters
/// The encoded data is is not padded
/// Lines are not separated
std::string encode3501(const std::string_view input);

/// @brief Base64 decoding using RFC 3501 (IMAP mailbox names) specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `+` as 62nd and `,` as 63rd characters
/// The encoded data is is not padded
/// Lines are not separated
std::optional<std::string> decode3501(const std::string_view input);

/// @brief Base64 encoding using RFC 4648.4 (standard) specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is is padded with `=` (optional)
/// Lines are not separated
std::string encode4648_4(const std::string_view input);

/// @brief Base64 decoding using RFC 4648.4 (standard) specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is padded with `=` (optional)
/// Lines are not separated
std::optional<std::string> decode4648_4(const std::string_view input);

/// @brief Base64 encoding using RFC 4648.4 (URL and filename safe)
/// specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `-` as 62nd and `_` as 63rd characters
/// The encoded data is is padded with `=` (optional)
/// Lines are not separated
std::string encode4648_5(const std::string_view input);

/// @brief Basd64 decoding using RFC 4648.4 (URL and filename safe)
/// specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `-` as 62nd and `_` as 63rd characters
/// The encoded data is padded with `=` (optional)
/// Lines are not separated
std::optional<std::string> decode4648_5(const std::string_view input);

/// @brief Base64 encoding using RFC 4880 (Radix-64 - OpenPGP) specification
///
/// @paramin input data to be encoded
/// @paramout encoded data
///
/// Uses `+` as 62nd and `/` as 63rd characters
/// The encoded data is is padded with `=` (mandatory)
/// Lines are at most 76 bytes long and separated with `CR+LF` (`\r\n`)
std::string encode4880(const std::string_view input);

/// @brief Basd64 decoding using RFC 4880 (Radix-64 - OpenPGP) specification
///
/// @paramin input data to be decoded
/// @paramout decoded data
///
/// Uses `-` as 62nd and `_` as 63rd characters
/// The encoded data is padded with `=` (optional)
/// Lines are at most 76 bytes long and separated with `CR+LF` (`\r\n`)
std::optional<std::string> decode4880(const std::string_view input);
} // namespace base64


extern "C"{

char* c_encode1421(char* input);
char* c_encode2045(char* input);
char* c_encode2152(char* input);
char* c_encode3501(char* input);
char* c_encode4648_4(char* input);
char* c_encode4648_5(char* input);
char* c_encode4880(char* input);

char* c_decode1421(char* input);
char* c_decode2045(char* input);
char* c_decode2152(char* input);
char* c_decode3501(char* input);
char* c_decode4648_4(char* input);
char* c_decode4648_5(char* input);
char* c_decode4880(char* input);





}