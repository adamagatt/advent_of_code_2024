#include "solutions.h"
#include "solution2.h"

#include "../utils/read.h"

#include <algorithm>
#include <numeric>

auto Solutions::solution2() -> Answers {

    auto input = Utils::readInts("inputs/input2.txt");

    int answerA = std::ranges::count_if(input, safe);
    int answerB = std::ranges::count_if(input, safeWithDampener);

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto safe(const std::vector<int>& row) -> bool {
    // A row is safe based on its jumps between elements and so we
    // calculate all of those jumps by computing the adjacent_difference
    // of the row. The row is safe if its diffs are all between 1 and 3
    // (if ascending) or between -1 and -3 (if descending).

    std::vector<int> diffs{};
    std::adjacent_difference(
        row.begin(), row.end(),
        std::back_inserter(diffs)
    );
    diffs.erase(diffs.begin()); // First adjacent_difference result is junk

    return std::ranges::all_of(diffs, [](int diff){return diff >=1 && diff <=3;})
        || std::ranges::all_of(diffs, [](int diff){return diff >=-3 && diff <=-1;});
}

auto safeWithDampener(const std::vector<int>& row) -> bool {
    if (safe(row)) return true; // Early exit if already safe

    // Dampened vector that drops a number, initially dropping the first number
    // and including the rest of the row
    std::vector<int> dampened(std::next(row.begin(), 1), row.end());

    // We will check if the dampened row is now safe, and if not then we will
    // substitute the 0th number from the original row and check again. Then
    // we will substitute the 1st and then 2nd and so on, placing each into
    // their original position.
    // e.g.  1 2 3 4 5   (row from 1-end leaves out 0)
    //       0 2 3 4 5   (bringing in 0 leaves out 1)
    //       0 1 3 4 5   (bringing in 1 leaves out 2), etc.
    if (safe(dampened)) return true;
    for (int i = 0; i < row.size() - 1; ++i) {
        dampened[i] = row[i];
        if (safe(dampened)) return true;
    }

    // No dropped number resulted in a safe row
    return false;
}