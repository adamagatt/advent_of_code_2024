#include "solutions.h"
#include "solution3.h"

#include "../utils/read.h"

#include <numeric>

auto Solutions::solution3() -> Answers {

    // Input appears split across several lines so I want to ensure I
    // read them as a single large string. This will be important for
    // Part B, which has state that persists between lines.
    auto input = Utils::readAsSingleLine("inputs/input3.txt");

    int answerA = processLinePartA(input);
    int answerB = processLinePartB(input);

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto processLinePartA(const std::string& line) -> int {
    // We will use the regex library to look for valid mul instructions.
    // The library has some performance issues but will be sufficient for
    // this exercise.

    // Apply our regex pattern to the line to set up start iterator, and create end
    auto muls_begin = std::sregex_iterator(line.begin(), line.end(), mul_pattern);
    auto muls_end = std::sregex_iterator();

    // Process every valid mul expression found and sum them
    return std::transform_reduce(
        muls_begin, muls_end,
        0, std::plus{},
        resultOfMul
    );
}

auto processLinePartB(const std::string& line) -> int {
    // We now need a compound regex that can pick up do, don't and mul
    // statements.
    auto muls_begin = std::sregex_iterator(line.begin(), line.end(), mul_do_dont_pattern);
    auto muls_end = std::sregex_iterator();

    // We can't use a simple transform_reduce anymore since we have state that
    // persists between tokens (our enabledness). Arguably we could use a complex
    // accumulator that tracks this state and only sums if we are enabled but
    // at this point I think it would be more readable to just handle the state
    // tracking, mul-calculations and accumulation manually.
    int total = 0;
    bool enabled = true;
    for (auto it = muls_begin; it != muls_end; ++it) {
        const std::smatch match = *it;

        if (match[0] == do_match) { // match[0] captures entire expression
            enabled = true;
        } else if (match[0] == dont_match) {
            enabled = false;
        } else {
            // This must be a mul pattern now, so process it if we are enabled
            if (enabled) {
                total += resultOfMul(match);
            }
        }
    }

    return total;
}

auto resultOfMul(const std::smatch& match) -> int {
    // Accepting a valid match of our regex pattern we can simply extract
    // the two components and multiply them. These components are match[1]
    // and [2], with [0] containing the entirety of the match.
    int firstNum = std::stoi(match[1].str());
    int secondNum = std::stoi(match[2].str());

    return firstNum * secondNum;
}