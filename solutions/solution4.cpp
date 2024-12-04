#include "solutions.h"
#include "solution4.h"

auto Solutions::solution4() -> Answers {

    auto input = Utils::readGrid<edgeLength, edgeLength>("inputs/input4.txt");

    // A simple brute force search. We scan the full grid for X's, and
    // for each one we search along all 8 directions for full words.

    int answerA = 0;
    for (int r = 0; r < edgeLength; ++r) {
        for (int c = 0; c < edgeLength; ++c) {
            // If we find an X we can begin searching outwards in straight lines
            if (input[r][c] == 'X') {
                // Obtain the guard checks we need to begin searching in a
                // particular direction, and the offsets needed for the search
                for (const auto& [rowCheck, colCheck, steps] : directionEntry) {
                    // If we are not too close to the grid edges for this particular
                    // direction then we can attempt a search
                    if (rowCheck(r) && colCheck(c)) {
                        if (search_in_direction(input, r, c, steps)) answerA++;
                    }
                }
            }
        }
    }

    int answerB = 0;
    // X shape requires the starting coordinate to not be on the
    // very edge of the grid
    for (int r = 1; r < edgeLength-1; ++r) {
        for (int c = 1; c < edgeLength-1; ++c) {
            if (x_mas_at_coords(input, r, c)) answerB++;
        }
    }

    return {std::to_string(answerA), std::to_string(answerB)};
}

auto search_in_direction(
    const Utils::Grid<140, 140>& input,
    int startRow,
    int startCol,
    const DirectionOffset& steps
) -> bool {
    for (int step = 0; step < numSteps; ++step) {
        int r = startRow + steps[step][0];
        int c = startCol + steps[step][1];
        if (input[r][c] != nextLetters[step]) {
            // Didn't find the required letter at the next search location so we fail
            return false;
        }
    }

    // Successfully completed all steps
    return true;
}

auto x_mas_at_coords(const Utils::Grid<edgeLength, edgeLength>& input, int aRow, int aCol) -> bool {
    // The provided coordinates are the 'A' at the centre of the X and so
    // we must satisfy that to begin with
    if (input[aRow][aCol] != 'A') return false;

    return ( // Backslash reads "MAS" or "SAM"
        (input[aRow-1][aCol-1] == 'M' && input[aRow+1][aCol+1] == 'S') ||
        (input[aRow-1][aCol-1] == 'S' && input[aRow+1][aCol+1] == 'M')
    ) && ( // Forward slash reads "MAS" or "SAM"
        (input[aRow-1][aCol+1] == 'M' && input[aRow+1][aCol-1] == 'S') ||
        (input[aRow-1][aCol+1] == 'S' && input[aRow+1][aCol-1] == 'M')
    );
}