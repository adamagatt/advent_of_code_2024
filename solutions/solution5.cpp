#include "solutions.h"
#include "solution5.h"

#include "../utils/read.h"

#include <algorithm>
#include <sstream>

auto Solutions::solution5() -> Answers {

    // A rule of A|B means that, if both A and B are present, then A
    // needs to appear before B. This means that the rule is violated 
    // iff B is encountered and then later A is encountered. If no rule
    // is violated in this way then the safety manual is correct.

    // To represent this logic I will use a map of B -> {A0 A1 A2}, where
    // each B is associated with a set of all pages that must come before
    // it. These pages go into a watchlist (set) and if any are encountered
    // then a rule has been violated.

    auto input = Utils::readLines("inputs/input5.txt");

    const auto& [violationRules, manuals] = parseInput(input);

    std::vector<Manual> incorrectlyOrderedManuals{};

    int answerA = 0;
    for (const auto& manual : manuals) {
        if (correctlyOrdered(manual, violationRules)) {
            // Add middle element to accumulator
            answerA += getMiddlePage(manual);
        } else {
            // Remember the incorrectly ordered manuals for Part B
            incorrectlyOrderedManuals.push_back(manual);
        }
    }

    // For part B I can use the violation rules as a guide to a sort
    // function with a custom comparator. The comparator can determine
    // the ordering of A and B by checking if B->A is a violation and,
    // if so, returning "true" to indicate that A is ordered before B.

    int answerB = 0;
    for (auto& manual : incorrectlyOrderedManuals) { // Non-const as we will sort these
        std::sort(
            manual.begin(), manual.end(),
            [&violationRules](int pageA, int pageB){return pageComparator(pageA, pageB, violationRules);}
        );
        answerB += getMiddlePage(manual);
    }

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto parseInput(const std::vector<std::string>& input) -> std::pair<ViolationRules, std::vector<Manual>> {
    // Process the ordering rules from all lines up until 
    // the empty line
    ViolationRules violationRules {};
    auto line = input.begin();
    for (; !line->empty(); ++line) {
        // Pattern is ##|##
        int beforePage = std::stoi(line->substr(0, 2));
        int afterPage = std::stoi(line->substr(3, 2));

        violationRules[afterPage].insert(beforePage);
    }

    ++line; // Skip empty line

    // Process each subsequent line as a manual
    std::vector<Manual> manuals{};
    for (; line != input.end(); ++line) {
        auto& currentManual = manuals.emplace_back();
        std::stringstream stream(*line);
        std::string token;

        while(getline(stream, token, ',')) {
            currentManual.push_back(std::stoi(token));
        }
    }

    return {violationRules, manuals};
}

auto correctlyOrdered(const Manual& manual, const ViolationRules& violationRules) -> bool {
    std::unordered_set<int> watchlist {};

    for (int page : manual) {
        // If we encounter a page on the watchlist then the book has violated a
        // precedence rule and must be incorrectly ordered
        if (watchlist.contains(page)) {
            return false;
        } else if (const auto& rule = violationRules.find(page); rule != violationRules.end()) {
            // If this page needed to go after some other pages then add those
            // other pages to the watchlist
            const auto& [_, pagesBefore] = *rule;
            watchlist.insert(pagesBefore.begin(), pagesBefore.end());
        }
    }

    // The book has not violated any precedence rules
    return true;
}

auto getMiddlePage(const Manual& manual) -> int {
    return *std::next(manual.begin(), manual.size()/2);
}

auto pageComparator(int pageA, int pageB, const ViolationRules& rules) -> bool {
    if (const auto& rule = rules.find(pageB); rule != rules.end()) {
        // An entry indicates that other pages must come before B
        const auto& [_, pagesBefore] = *rule;
        if (pagesBefore.contains(pageA)) {
            // A is one of those pages, so comparator returns true
            return true;
        }
    }
    // We have no information that A must come before B
    return false;
}