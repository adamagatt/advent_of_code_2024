#include "solutions.h"

#include "../utils/read.h"

#include <iostream>
#include <numeric>
#include <unordered_map>

auto Solutions::solution1() -> Answers {

    auto input = Utils::readTokens<2>("inputs/input1.txt");

    // Tokenise and parse each line to create our two lists of ints
    constexpr size_t LIST_LENGTH = 1'000;
    std::array<int, LIST_LENGTH> leftList;
    std::array<int, LIST_LENGTH> rightList;
    
    for (int i = 0; i < LIST_LENGTH; ++i) {
        leftList[i] = std::stoi(input[i][0]);
        rightList[i] = std::stoi(input[i][1]);
    }

    // *** PART A SOLUTION ***
    // We need to sort both lists and zip pairs of elements together. The
    // distance between a pair of numbers is their absolute difference. We
    // can zip the lists with an overload of transform_reduce that accepts
    // two start iterators.

    std::ranges::sort(leftList);
    std::ranges::sort(rightList);

    int answerA = std::transform_reduce(
        leftList.begin(), leftList.end(),
        rightList.begin(),
        // 2) Sum up all the calculated distances, accumulating from 0
        0, std::plus{},
        // 1) Calculate distance of each pair of numbers
        [](int l, int r){return abs(l-r);} 
    );    

    // *** PART B SOLUTION ***
    // We need to turn the right list into a Counter, basically a map of
    // <value, frequency> pairs that can be built using an unordered_map. Then
    // for each element in the left list we index into our built counter to
    // find the number of occurrences.

    std::unordered_map<int, unsigned int> counter{};

    for (int value : rightList) {
        // It is safe to build a counter from a map using raw indexing ([]),
        // as indexing into a key that does not exist will result in its creation
        // with its type's default value, which for an unsigned int is 0. This
        // results in an oddly elegant way to build a counter that appears like
        // it is missing edge-case logic but isn't. 
        counter[value]++;
    }

    int answerB = std::transform_reduce(
        leftList.begin(), leftList.end(),
        // 2) Sum up calculated value again
        0, std::plus{},
        // 1) Calculate each item in the left list by its value multiplied
        //    by its frequency from the right list's counter.
        [&counter](int l){return l * counter[l];} 
    );    

    return {std::to_string(answerA), std::to_string(answerB)};
}