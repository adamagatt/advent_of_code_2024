cmake_minimum_required(VERSION 3.20.0)
project(aoc24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(SOURCES
    main.cpp

    solutions/solutions.cpp
    solutions/solution1.cpp
    solutions/solution2.cpp
    solutions/solution3.cpp

    utils/read.cpp
)

set(INPUTS
    inputs/input1.txt
    inputs/input2.txt
    inputs/input3.txt
)

add_executable(aoc24 ${SOURCES})

install(TARGETS aoc24 RUNTIME DESTINATION "install" )
install(FILES ${INPUTS} DESTINATION "install/inputs")