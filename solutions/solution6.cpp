#include "solutions.h"
#include "solution6.h"

#include <numeric>

auto Solutions::solution6() -> Answers {

    const auto original_map = Utils::readGrid<130, 130>("inputs/input6.txt");
    Location start_location = find_start(original_map);

    // Initial walk of the original map for Part A with no map modifications.
    // Result of walk_map() is ignored as we assume no infinite loop will
    // occur with the original map.
    auto map = original_map; // Make copy as walk_map modifies the input
    walk_map(map, start_location); 
    int answerA = count_walked(map);

    // For Part B we iterate through all empty map locations, insert a single
    // wall there and walk the map to determine if an infinite loop will occur
    int answerB = 0;
    // for (int r = 0; r < rows; ++r) {
    //     for (int c = 0; c < cols; ++c) {
    //         // Found an originally-empty location to try a wall
    //         if (original_map[r][c] == sym_empty) {
    //             map = original_map;
    //             map[r][c] = sym_wall;
    //             if (walk_map(map, start_location) == WalkResult::Loop) {
    //                 answerB++;
    //             }
    //         }
    //     }
    // }

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto turn_right(const DirectionItr& direction) -> DirectionItr {
    DirectionItr out = std::next(direction);
    
    return out != directions.end() ? out : directions.begin();
}

auto find_start(const Map& map) -> Location {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (map[r][c] == '^') return {r, c};
        }
    }

    return {-1, -1};
}

auto outside_map(const Location& location) -> bool {
    return location.first < 0
        || location.first >= rows
        || location.second < 0
        || location.second >= cols;
}

auto mark_walked(Map& map, const Location& location) -> void {
    map[location.first][location.second] = sym_walked;
}

auto walk_map(Map& map, const Location& start_location) -> WalkResult {
    // Begin at starting location facing upwards
    Location location = start_location;
    DirectionItr direction = directions.begin();

    mark_walked(map, location);

    while (true) {
        Location next_step = {
            location.first + direction->first,
            location.second + direction->second
        };

        // Check if left map
        if (outside_map(next_step)) {
            return WalkResult::LeftMap;
        } else if (next_step == start_location && direction == directions.begin()) {
            return WalkResult::Loop;
        }

        // Check if in infinite loop by determining if the
        // next step will place the path back at the start
        // location and facing upwards

        switch (map[next_step.first][next_step.second]) {
            case sym_empty:
            case sym_start: // Fallthrough
            case sym_walked: // Fallthrough
                mark_walked(map, next_step);
                location = next_step;
                break;
            case sym_wall:
                direction = turn_right(direction);
                break;
        }
    }
}

auto count_walked(const Map& map) -> size_t {
    return std::transform_reduce(
        map.begin(), map.end(),
        0, std::plus{},
        [](const Utils::Row<cols>& col){return std::ranges::count(col, sym_walked);}
    );
}

auto operator==(const Location& lhs, const Location& rhs) -> bool {
    return lhs.first == rhs.first
        && lhs.second == rhs.second;
}