#include "read.h"

auto Utils::parseIntChar(char c) -> int {
    return c - '0';
}

auto Utils::readLines(const char* path) -> std::vector<std::string>{
    std::vector<std::string> output;

    std::ifstream fileIn(path);
    for (std::string line; std::getline(fileIn, line);) {
        output.push_back(line);
    }

    return output;
}

auto Utils::readAsSingleLine(const char* path) -> std::string {
    std::string output;

    std::ifstream fileIn(path);
    for (std::string line; std::getline(fileIn, line);) {
        output.append(line);
    }

    return output;
}

auto Utils::readInts(const char* path) -> std::vector<std::vector<int>> {
    std::vector<std::vector<int>> output;

    std::ifstream fileIn(path);
    for (std::string line; std::getline(fileIn, line);) {
        std::stringstream ss(line);
        std::vector<int>& row = output.emplace_back();
        int num;
        while (ss >> num) {
            row.push_back(num);
        }
    }

    return output;
}