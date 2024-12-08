#include "solutions.h"
#include "solution8.h"

#include <numeric>

auto Solutions::solution8() -> Answers {

    const auto map = Utils::readGrid<edgeLength, edgeLength>("inputs/input8.txt");
    const auto& symbolLocations = getSymbolLocations(map);

    int answerA{};
    int answerB{};

    std::array<std::pair<int&, AntinodeGenerator>, 2> parts = {{
        {answerA, potentialAntinodeLocationsPartA},
        {answerB, potentialAntinodeLocationsPartB}
    }};

    for (auto& [result, antinodeGenerator] : parts) {
        std::set<Location> antinodes{};
        for (const auto& [symbol, locations]: symbolLocations) {
            const auto newAntinodes = getAntinodes(locations, antinodeGenerator);
            antinodes.insert(newAntinodes.begin(), newAntinodes.end());
        }
        result = antinodes.size();
    }

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto withinMap(const Location& location) -> bool {
    return location.col >=0
        && location.col < edgeLength
        && location.row >= 0
        && location.row < edgeLength;
}

auto getSymbolLocations(const Utils::Grid<edgeLength, edgeLength>& map) -> SymbolLocations {
    SymbolLocations symbolLocations{};

    for (int r = 0; r < edgeLength; ++r) {
        for (int c = 0; c < edgeLength; ++c) {
            char curChar = map[r][c];
            if (curChar != '.') {
                symbolLocations[curChar].emplace_back(r, c);
            }
        }
    }

    return symbolLocations;
}

auto getAntinodes(const std::vector<Location>& antennae, AntinodeGenerator antinodeGenerator) -> std::set<Location> {
    std::set<Location> antinodes {};

    // Loop through all possible pairs of antinodes (of the same symbol)
    for (auto antenna1 = antennae.begin(); antenna1 != antennae.end(); ++antenna1) {
        for (auto antenna2 = std::next(antenna1, 1); antenna2 != antennae.end(); ++antenna2) {
    
            auto potentialAntinodes = antinodeGenerator(*antenna1, *antenna2);

            // Add any that fall within the map to our output list
            for (const auto& antinode : potentialAntinodes) {
                if (withinMap(antinode)) {
                    antinodes.insert(antinode);
                }
            }
        }
    }

    return antinodes;
}

auto potentialAntinodeLocationsPartA(const Location& antenna1, const Location& antenna2) -> std::vector<Location> {
    const Location diff = antenna1 - antenna2;

    // Two potential antinodes for each pair of antennae
    return {
        antenna1 + diff,
        antenna2 - diff
    };
}

auto potentialAntinodeLocationsPartB(const Location& antenna1, const Location& antenna2) -> std::vector<Location> {
    std::vector<Location> antinodes;

    const Location diff = antenna1 - antenna2;

    // Check repeated antinodes forward from antenna1 and backwards from antenna2
    Location antinode = antenna1;
    while (withinMap(antinode)) {
        antinodes.push_back(antinode);
        antinode = antinode + diff;
    }

    antinode = antenna2;
    while (withinMap(antinode)) {
        antinodes.push_back(antinode);
        antinode = antinode - diff;
    }

    return antinodes;
}