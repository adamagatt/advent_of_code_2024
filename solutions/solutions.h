#ifndef __SOLUTIONS_H
#define __SOLUTIONS_H

#include <functional>
#include <string>
#include <utility>

namespace Solutions {
    using Answers = std::pair<std::string, std::string>;

    auto solution1() -> Answers;
    auto solution2() -> Answers;
    auto solution3() -> Answers;

    constexpr int MAX = 3;

    auto selectSolution() -> std::function<Answers()> ;
}

#endif