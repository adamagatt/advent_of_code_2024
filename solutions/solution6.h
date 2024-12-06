#ifndef __SOLUTION_6_H
#define __SOLUTION_6_H

#include "../utils/read.h"

#include <algorithm>
#include <utility>

constexpr int rows = 130;
constexpr int cols = 130;
constexpr char sym_walked = '*';
constexpr char sym_empty = '.';
constexpr char sym_wall = '#';
constexpr char sym_start = '^';

using Map = Utils::Grid<rows, cols>;
using Location = std::pair<size_t, size_t>;
using Direction = std::pair<int, int>;

constexpr std::array<Direction, 4> directions {{
    {-1,  0}, // Walk up (starting direction)
    { 0,  1}, // Walk right
    { 1,  0}, // Walk down
    { 0, -1}  // Walk left
}};

using DirectionItr = std::array<Direction, 4>::const_iterator;

enum class WalkResult {LeftMap, Loop};

auto turn_right(const DirectionItr& direction) -> DirectionItr;

auto find_start(const Map& map) -> Location;

auto outside_map(const Location& location) -> bool;

auto mark_walked(Map& map, const Location& location) -> void;

auto walk_map(Map& map, const Location& start_location) -> WalkResult;

auto count_walked(const Map& map) -> size_t;

auto operator==(const Location& lhs, const Location& rhs) -> bool;

#endif