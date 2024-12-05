#ifndef __SOLUTION_5_H
#define __SOLUTION_5_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using ViolationRules = std::unordered_map<int, std::unordered_set<int>>;
using Manual = std::vector<int>;

auto parseInput(const std::vector<std::string>& input) -> std::pair<ViolationRules, std::vector<Manual>>;

auto correctlyOrdered(const Manual& manual, const ViolationRules& violationRules) -> bool;

auto getMiddlePage(const Manual& manual) -> int;

auto isPageABeforeB(int pageA, int pageB, const ViolationRules& rules) -> bool;

#endif