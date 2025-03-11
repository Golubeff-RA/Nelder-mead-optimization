cmake_minimum_required(VERSION 3.12)

set (PROJECT_NAME functionParserTests)
project(${PROJECT_NAME} C CXX)

enable_testing()
add_executable(${PROJECT_NAME} tests/main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/FunctionReader/include)
target_link_libraries(${PROJECT_NAME} gtest gmock pthread)
