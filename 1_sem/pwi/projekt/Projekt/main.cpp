#include "base64.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    std::string input;

    auto encoder = base64::encode4648_4;
    auto decoder = base64::decode4648_4;

    const std::string usage =
        "usage: " + std::string(argv[0]) +
        " [ALGORITHM]\nALGORITHM: The RFC number that proposed the "
        "algorithm.\n\tFollowing RFCs are supported: 1421, 2045, 2152, 3501, "
        "4648_4, 4648_5, 4880.\n\tIf the algorithm is not specified 4648_4 "
        "will be used.";

    if (argc <= 1) {
        std::cerr << usage << std::endl;
        std::cerr << "Using the default algorithm: 4648_4" << std::endl;
        encoder = base64::encode4648_4;
        decoder = base64::decode4648_4;
    } else if (std::string(argv[1]) == "1421") {
        encoder = base64::encode1421;
        decoder = base64::decode1421;
    } else if (std::string(argv[1]) == "2045") {
        encoder = base64::encode2045;
        decoder = base64::decode2045;
    } else if (std::string(argv[1]) == "2152") {
        encoder = base64::encode2152;
        decoder = base64::decode2152;
    } else if (std::string(argv[1]) == "3501") {
        encoder = base64::encode3501;
        decoder = base64::decode3501;
    } else if (std::string(argv[1]) == "4648_4") {
        encoder = base64::encode4648_4;
        decoder = base64::decode4648_4;
    } else if (std::string(argv[1]) == "4648_5") {
        encoder = base64::encode4648_5;
        decoder = base64::decode4648_5;
    } else if (std::string(argv[1]) == "4880") {
        encoder = base64::encode4880;
        decoder = base64::decode4880;
    } else {
        std::cerr << usage << std::endl;
        return 0;
    }

    std::cout << "Enter text to be encoded:\n";
    std::getline(std::cin, input);

    std::string encoded = encoder(input);
    std::string decoded = decoder(encoded).value_or("<ERROR>");

    std::cout << "Text encoded with base64:\n" << encoded << "\n";
    std::cout << "Text decoded from base64:\n" << decoded << "\n";
}
