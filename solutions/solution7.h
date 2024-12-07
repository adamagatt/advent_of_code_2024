#ifndef __SOLUTION_7_H
#define __SOLUTION_7_H

#include <cmath>
#include <string>
#include <vector>

struct Equation {
    long target;
    std::vector<long> operands;
};

enum class Operator{Add, Multiply, Concatenate};

auto parseLine(const std::string& line) -> Equation;
auto testOperators(const Equation& equation, const std::vector<Operator>& operators) -> bool;

template <int N>
auto operatorsFromCode(unsigned int operatorCode, size_t numOperators) -> std::vector<Operator> {
    std::vector<Operator> operators{numOperators, Operator::Add};

    for (int i = 0; i < numOperators; ++i) {
        unsigned int remainder = operatorCode % N;
        if (remainder == 1) {
            operators[i] = Operator::Multiply;
        } else if (remainder == 2) { // Only available when N > 2 (i.e. Part B)
            operators[i] = Operator::Concatenate;
        }
        operatorCode /= N; // If we only needed to support Part A then >>= 1 is better
    }

    return operators;
}

template <int N>
auto getCalibrationResult(const std::vector<Equation> equations) -> unsigned long {
    unsigned long calibrationResult = 0;
    for (const auto& equation : equations) {
        
        // We need one fewer operator than operands
        size_t numOperators = equation.operands.size() - 1;
        unsigned int maxOperatorCode = pow(N, numOperators) - 1;

        for (int operatorCode = 0; operatorCode <= maxOperatorCode; ++operatorCode) {
            auto operators = operatorsFromCode<N>(operatorCode, numOperators);
            if (testOperators(equation, operators)) { // Success!
                calibrationResult += equation.target;
                break;
            }
        }
    }

    return calibrationResult;
}

#endif