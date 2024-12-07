#include "solutions.h"
#include "solution7.h"

#include "../utils/read.h"

#include <algorithm>
#include <sstream>

auto Solutions::solution7() -> Answers {

    const auto input = Utils::readLines("inputs/input7.txt");

    std::vector<Equation> equations{};
    std::ranges::transform(input, std::back_inserter(equations), parseLine);

    // To cycle through all particular operators at all positions we will have
    // an "operator code" that is a numeric representation of the chosen
    // operators that we can increment repeatedly and check each value.
    //
    // The operator code is an N-ary representation of the operators, binary
    // for Part A and ternary for part B. Each digit represents an operator
    // where a 0 digit is "add", 1 is "multiply" and 2 is "concatenate".
    //
    // For an example. If we need 3 operators for Part A then we might
    // have operator code 5, which in binary is [1 0 1]
    // This represents [multiply, add, multiply] and so we want to calculate:
    // value1 * value2 + value3 * value4
    //
    // The same operator code 5 in Part B is interpreted as the ternary [0 1 2]
    // This represents [add, multiply, concatenate] and so we calculate:
    // value1 + value2 * value3 || value4
    //
    // This allows for (O^N-1) unique codes where where O is the number of
    // operators required and N is 2 for Part A and 3 for Part B. We check
    // all codes from 0 up to this maximum and return true if we find one
    // that results in a set of operators that allow an equation to match its
    // target result.

    unsigned long answerA = getCalibrationResult<2>(equations);
    unsigned long answerB = getCalibrationResult<3>(equations);

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto parseLine(const std::string& line) -> Equation {
    Equation equation{};
    std::stringstream stream(line);
    std::string token;

    getline(stream, token, ':');
    stream.ignore(1); // Skip past the ' ' after the ':'
    equation.target = std::stol(token);

    while(getline(stream, token, ' ')) {
        equation.operands.push_back(std::stol(token));
    }

    return equation;
}

auto testOperators(const Equation& equation, const std::vector<Operator>& operators) -> bool {
    long accumulator = equation.operands[0];

    for (int i = 0; i < operators.size(); ++i) {
        long value = equation.operands[i+1];
        switch (operators[i]) {
            case Operator::Add:
                accumulator += value;
                break;
            case Operator::Multiply:
                accumulator *= value;
                break;
            case Operator::Concatenate:
                size_t digitsInValue = std::to_string(value).size();
                accumulator = accumulator * pow(10, digitsInValue) + value;
        }
    }

    return accumulator == equation.target;
}