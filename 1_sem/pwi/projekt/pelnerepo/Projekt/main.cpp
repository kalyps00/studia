#include "arithmetic.hpp"
#include "base64.hpp"

#include <fstream>
#include <iostream>

bool base64_example(int argc, char *argv[]) {
    auto encoder = base64::encode4648_4;
    auto decoder = base64::decode4648_4;

    if (argc < 1) {
        std::cerr << "Using the default algorithm: 4648_4\n";
    } else {
        auto algorithm = std::string(argv[0]);
        if (algorithm == "1421") {
            encoder = base64::encode1421;
            decoder = base64::decode1421;
        } else if (algorithm == "2045") {
            encoder = base64::encode2045;
            decoder = base64::decode2045;
        } else if (algorithm == "2152") {
            encoder = base64::encode2152;
            decoder = base64::decode2152;
        } else if (algorithm == "3501") {
            encoder = base64::encode3501;
            decoder = base64::decode3501;
        } else if (algorithm == "4648_4") {
            encoder = base64::encode4648_4;
            decoder = base64::decode4648_4;
        } else if (algorithm == "4648_5") {
            encoder = base64::encode4648_5;
            decoder = base64::decode4648_5;
        } else if (algorithm == "4880") {
            encoder = base64::encode4880;
            decoder = base64::decode4880;
        } else {
            std::cerr << "Wrong algorithm: " << algorithm << "\n";
            return false;
        }
    }

    std::string input;

    std::cout << "Enter text to be encoded:" << std::endl;
    std::getline(std::cin, input);

    std::string encoded = encoder(input);
    std::string decoded = decoder(encoded).value_or("<ERROR>");

    std::cout << "Text encoded with base64:\n" << encoded << "\n";
    std::cout << "Text decoded from base64:\n" << decoded << "\n";

    return true;
}

bool arithmetic_example(int argc, char *argv[]) {
    if (argc < 1) {
        std::cerr << "Error: missing input path\n";
        return false;
    }

    auto input_path = std::string(argv[0]);
    auto input_stream = std::ifstream(input_path);

    if (!input_stream.is_open()) {
        std::cerr << "Error: cannot open given file: " << input_path << "\n";
        return false;
    }

    std::string compressed_path = input_path + ".comp";
    std::string decompressed_path = input_path + ".decomp";

    std::cout << "Compressing to '" << compressed_path << "' ...";
    bitio::bit_ofstream compressed_stream(compressed_path);
    arithmetic::compress(input_stream, compressed_stream);
    std::cout << " Done." << std::endl;

    std::cout << "Decompressing to '" << decompressed_path << "' ...";
    bitio::bit_ifstream input_stream2(compressed_path);
    auto decompressed_stream = std::ofstream(decompressed_path);
    arithmetic::decompress(input_stream2, decompressed_stream);
    std::cout << " Done." << std::endl;

    return true;
}

int main(int argc, char *argv[]) {
    const std::string usage =
        "usage: " + std::string(argv[0]) + " <COMMAND>\n"
        "COMMANDS:\n"
        "\tbase64 [ALGORITHM]\n"
        "\t\tAsks for an input and prints it's encoded and decoded forms.\n"
        "\n"
        "\t\tALGORITHM: The RFC number that proposed the algorithm.\n"
        "\t\t\tFollowing RFCs are supported: 1421, 2045, 2152, 3501\n"
        "\t\t\t4648_4, 4648_5, 4880.\n"
        "\t\t\tIf the algorithm is not specified 4648_4 will be used.\n"
        "\n"
        "\tarithmetic <INPUT PATH>\n"
        "\t\tCompresses the file into a file with a '.comp' extension, which\n"
        "\t\tis then decompressed into a file with a '.decomp' extension";

    if (argc <= 1) {
        std::cerr << usage << std::endl;
        return 0;
    }

    std::string command = std::string(argv[1]);
    bool result = true;

    if (command == "help") {
        std::cerr << usage << std::endl;
        return 0;
    } else if (command == "base64") {
        result = base64_example(argc - 2, argv + 2);
    } else if (command == "arithmetic") {
        result = arithmetic_example(argc - 2, argv + 2);
    } else {
        std::cerr << "Error: Wrong command: " << command << "\n";
        result = false;
    }

    if (!result) {
        std::cerr << usage << std::endl;
        return 1;
    }
}
