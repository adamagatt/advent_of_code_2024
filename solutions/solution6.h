#ifndef __SOLUTION_6_H
#define __SOLUTION_6_H

#include "../utils/read.h"

#include <algorithm>
#include <utility>

constexpr int rows = 130;
constexpr int cols = 130;
constexpr char sym_empty = '.';
constexpr char sym_wall = '#';
constexpr char sym_start = '^';

using Map = Utils::Grid<rows, cols>;
using Location = std::pair<size_t, size_t>;
using VisitedMap = std::array<std::array<std::array<bool, 4>, cols>,rows>;

enum class Direction {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3
};

using StepOffset = std::pair<int, int>;
constexpr std::array<StepOffset, 4> step_offsets {{
    {-1,  0}, // Walk up (starting direction)
    { 0,  1}, // Walk right
    { 1,  0}, // Walk down
    { 0, -1}  // Walk left
}};

enum class WalkResult {LeftMap, Loop};

auto turn_right(Direction direction) -> std::pair<Direction, StepOffset>;

auto find_start(const Map& map) -> Location;

auto outside_map(const Location& location) -> bool;

auto mark_walked(VisitedMap& visitedMap, const Location& location, Direction direction) -> void;

auto walk_map(const Map& map, const Location& start_location) -> std::pair<WalkResult, VisitedMap>;

auto count_walked(const VisitedMap& visitedMap) -> size_t;

#endif