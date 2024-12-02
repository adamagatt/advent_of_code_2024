#ifndef __SOLUTIONS_H
#define __SOLUTIONS_H

#include <functional>
#include <string>
#include <utility>

namespace Solutions {
    using Answers = std::pair<std::string, std::string>;

    auto solution1() -> Answers;

    constexpr int MAX = 1;

    auto selectSolution() -> std::function<Answers()> ;
}

#endif