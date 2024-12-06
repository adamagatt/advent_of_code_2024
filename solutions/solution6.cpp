#include "solutions.h"
#include "solution6.h"

#include <functional>
#include <numeric>

auto Solutions::solution6() -> Answers {

    const auto original_map = Utils::readGrid<rows, cols>("inputs/input6.txt");
    Location start_location = find_start(original_map);

    // Initial walk of the original map for Part A with no map modifications.
    // Result of walk_map() is ignored as we assume no infinite loop will
    // occur with the original map.
    auto map = original_map; // Make copy as walk_map modifies the input
    const auto& [_, visitedMap] = walk_map(map, start_location); 
    int answerA = count_walked(visitedMap);

    // For Part B we iterate through all empty map locations, insert a single
    // wall there and walk the map to determine if an infinite loop will occur
    int answerB = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // Found an originally-empty location to try a wall
            if (original_map[r][c] == sym_empty) {
                // Clone the map and add that extra wall
                map = original_map;
                map[r][c] = sym_wall;
                // Walk the modified map and determine if a loop occurred
                const auto& [walkResult, _] = walk_map(map, start_location); 
                if (walkResult == WalkResult::Loop) {
                    answerB++;
                }
            }
        }
    }

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto turn_right(Direction direction) -> std::pair<Direction, StepOffset> {
    Direction newDirection;
    switch (direction) {
        case Direction::Up:
            newDirection = Direction::Right;
            break;
        case Direction::Right:
            newDirection = Direction::Down;
            break;
        case Direction::Down:
            newDirection = Direction::Left;
            break;
        case Direction::Left:
            newDirection = Direction::Up;
            break;
    }

    return {newDirection, step_offsets[static_cast<int>(newDirection)]};
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

auto mark_walked(VisitedMap& visitedMap, const Location& location, Direction direction) -> void {
    visitedMap[location.first][location.second][static_cast<int>(direction)] = true;
}

auto walk_map(const Map& map, const Location& start_location) -> std::pair<WalkResult, VisitedMap> {
    // Begin at starting location facing upwards
    Location location = start_location;
    Direction direction = Direction::Up;
    StepOffset step_offset = step_offsets[static_cast<int>(direction)];
    VisitedMap visitedMap {};

    mark_walked(visitedMap, location, direction);

    while (true) {
        Location next_step = {
            location.first + step_offset.first,
            location.second + step_offset.second
        };

        // Check if next step is outside map
        if (outside_map(next_step)) {
            return {WalkResult::LeftMap, visitedMap};
        } else if (visitedMap[next_step.first][next_step.second][static_cast<int>(direction)]) {
            // Check if we are re-visiting the same tile and with the same direction too
            return {WalkResult::Loop, visitedMap};
        }

        // Otherwise we are fine to continue walking, so either advance or
        // turn depending on the tile we are about to enter
        switch (map[next_step.first][next_step.second]) {
            case sym_empty: // Fallthrough
            case sym_start:
                location = next_step;
                mark_walked(visitedMap, location, direction);
                break;
            case sym_wall:
                auto turnResult = turn_right(direction);
                direction = turnResult.first;
                step_offset = turnResult.second;
                break;
        }
    }
}

auto count_walked(const VisitedMap& visitedMap) -> size_t {
    size_t walked = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // Count the tile if it was walked over from any direction
            if (std::ranges::any_of(visitedMap[r][c], std::identity{})) {
                walked++;
            }
        }
    }

    return walked;
}