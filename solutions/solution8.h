#ifndef __SOLUTION_8_H
#define __SOLUTION_8_H

#include "../utils/read.h"

#include <unordered_map>
#include <set>
#include <vector>

constexpr size_t edgeLength = 50;

struct Location {
    int row{};
    int col{};

    auto operator+(const Location& rhs) const -> Location {
        return {row + rhs.row, col + rhs.col};
    }

    auto operator-(const Location& rhs) const -> Location {
        return {row - rhs.row, col - rhs.col};
    }

    auto operator<(const Location& rhs) const -> bool {
        return row != rhs.row
             ? row < rhs.row
             : col < rhs.col;
    }
};

using SymbolLocations = std::unordered_map<char, std::vector<Location>>;

auto withinMap(const Location& location) -> bool;

auto getSymbolLocations(const Utils::Grid<edgeLength, edgeLength>& map) -> SymbolLocations;

using AntinodeGenerator = std::vector<Location>(*)(const Location& antenna1, const Location& antenna2);
auto getAntinodes(const std::vector<Location>& antennae, AntinodeGenerator antinodeGenerator) -> std::set<Location>;
auto potentialAntinodeLocationsPartA(const Location& antenna1, const Location& antenna2) -> std::vector<Location>;
auto potentialAntinodeLocationsPartB(const Location& antenna1, const Location& antenna2) -> std::vector<Location>;

#endif