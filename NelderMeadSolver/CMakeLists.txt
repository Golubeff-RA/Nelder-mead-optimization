cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

enable_testing()

set(POINT_DIR ${CMAKE_SOURCE_DIR}/Points)
set(FUNCTION_DIR ${CMAKE_SOURCE_DIR}/FunctionReader)

add_executable(playground 
    src/playground.cpp 
    ${CMAKE_SOURCE_DIR}/Points/src/constructors.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/operators.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/measure.cpp
    ${CMAKE_SOURCE_DIR}/NelderMeadSolver/src/solver.cpp
)
add_executable(${PROJECT_NAME}.tests 
    tests/solverTesting.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/constructors.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/operators.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/measure.cpp
    ${CMAKE_SOURCE_DIR}/NelderMeadSolver/src/solver.cpp
)
include_directories(
    ${CMAKE_SOURCE_DIR}/FunctionReader/include
    ${CMAKE_SOURCE_DIR}/NelderMeadSolver/include
    ${CMAKE_SOURCE_DIR}/Points/include
)
target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread)