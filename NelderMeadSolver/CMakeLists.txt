cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

enable_testing()

set(POINT_DIR ${CMAKE_SOURCE_DIR}/Points)
set(FUNCTION_DIR ${CMAKE_SOURCE_DIR}/FunctionReader)
set(SOLVER_DIR ${CMAKE_SOURCE_DIR}/NelderMeadSolver)

add_library(solver SHARED
    ${SOLVER_DIR}/src/solver.cpp
)

add_executable(${PROJECT_NAME} 
    src/playground.cpp 
)
add_executable(${PROJECT_NAME}.tests 
    tests/solverTesting.cpp
)
include_directories(
    ${CMAKE_SOURCE_DIR}/FunctionReader/include
    ${CMAKE_SOURCE_DIR}/NelderMeadSolver/include
    ${CMAKE_SOURCE_DIR}/Points/include
)
target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread function_parser )
target_link_libraries(${PROJECT_NAME} function_parser)