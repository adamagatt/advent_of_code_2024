#ifndef __SOLUTION_4_H
#define __SOLUTION_4_H

#include "../utils/read.h"

#include <array>

constexpr int edgeLength = 140;

constexpr char firstLetter = 'X';
constexpr int numSteps = 3;
constexpr std::array<char, numSteps> nextLetters {'M', 'A', 'S'};

// Helper utilities to determine if we are too close to the edge of the grid
// to be able to search in a particular direction
using CoordCheck = bool(*)(int);
constexpr CoordCheck notAgainstLeft =   [](int col){return col >= 3;};
constexpr CoordCheck notAgainstRight =  [](int col){return col <= (edgeLength - 4);};
constexpr CoordCheck notAgainstTop =    [](int row){return row >= 3;};
constexpr CoordCheck notAgainstBottom = [](int row){return row <= (edgeLength - 4);};
constexpr CoordCheck noCheck =          [](int _){return true;};

// Coordinate offsets required to search in a straight line along each
// of the eight directions
using DirectionOffset = std::array<std::array<int, 2>, numSteps>;
constexpr DirectionOffset STEPS_LEFT       {{{{ 0, -1}}, {{ 0, -2}}, {{ 0, -3}}}};
constexpr DirectionOffset STEPS_RIGHT      {{{{ 0,  1}}, {{ 0,  2}}, {{ 0,  3}}}};
constexpr DirectionOffset STEPS_UP         {{{{-1,  0}}, {{-2,  0}}, {{-3,  0}}}};
constexpr DirectionOffset STEPS_DOWN       {{{{ 1,  0}}, {{ 2,  0}}, {{ 3,  0}}}};
constexpr DirectionOffset STEPS_UP_LEFT    {{{{-1, -1}}, {{-2, -2}}, {{-3, -3}}}};
constexpr DirectionOffset STEPS_UP_RIGHT   {{{{-1,  1}}, {{-2,  2}}, {{-3,  3}}}};
constexpr DirectionOffset STEPS_DOWN_LEFT  {{{{ 1, -1}}, {{ 2, -2}}, {{ 3, -3}}}};
constexpr DirectionOffset STEPS_DOWN_RIGHT {{{{ 1,  1}}, {{ 2,  2}}, {{ 3,  3}}}};

// The coordinate checks that need to pass to be able to search in each
// of the straight-line directions
using DirectionEntry = std::array<std::tuple<CoordCheck, CoordCheck, DirectionOffset>, 8>;
DirectionEntry directionEntry {{
    {notAgainstTop,    noCheck,         STEPS_UP},
    {notAgainstBottom, noCheck,         STEPS_DOWN},
    {noCheck,          notAgainstLeft,  STEPS_LEFT},
    {noCheck,          notAgainstRight, STEPS_RIGHT},
    {notAgainstTop,    notAgainstLeft,  STEPS_UP_LEFT},
    {notAgainstTop,    notAgainstRight, STEPS_UP_RIGHT},
    {notAgainstBottom, notAgainstLeft,  STEPS_DOWN_LEFT},
    {notAgainstBottom, notAgainstRight, STEPS_DOWN_RIGHT}
}};

auto search_in_direction(const Utils::Grid<edgeLength, edgeLength>& input, int startRow, int startCol, const DirectionOffset& steps) -> bool;
auto x_mas_at_coords(const Utils::Grid<edgeLength, edgeLength>& input, int aRow, int aCol) -> bool;

#endif