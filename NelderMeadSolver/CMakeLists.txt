cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

enable_testing()
add_executable(playground src/playground.cpp)
add_executable(${PROJECT_NAME}.tests tests/solverTesting.cpp)
include_directories(${CMAKE_SOURCE_DIR}/FunctionReader/include ${CMAKE_SOURCE_DIR}/NelderMeadSolver/include)
target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread)