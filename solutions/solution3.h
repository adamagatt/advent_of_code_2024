#ifndef __SOLUTION_3_H
#define __SOLUTION_3_H

#include <string>
#include <regex>

const std::regex mul_pattern{"mul\\((\\d+)\\,(\\d+)\\)"};
const std::regex mul_do_dont_pattern{"mul\\((\\d+)\\,(\\d+)\\)|do\\(\\)|don't\\(\\)"};
const char* do_match{"do()"};
const char* dont_match{"don't()"};

auto processLinePartA(const std::string& line) -> int;
auto processLinePartB(const std::string& line) -> int;
auto resultOfMul(const std::smatch& match) -> int;

#endif