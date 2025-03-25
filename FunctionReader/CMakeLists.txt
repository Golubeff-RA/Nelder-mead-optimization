cmake_minimum_required(VERSION 3.12)

set (PROJECT_NAME functionParserTests)
project(${PROJECT_NAME} C CXX)

enable_testing()
add_executable(
    ${PROJECT_NAME} tests/main.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/constructors.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/operators.cpp

)

add_executable(
    run src/StringDecode.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/constructors.cpp
    ${CMAKE_SOURCE_DIR}/Points/src/operators.cpp

)
include_directories(
    ${CMAKE_SOURCE_DIR}/FunctionReader/include
    ${CMAKE_SOURCE_DIR}/Points/include
)
target_link_libraries(${PROJECT_NAME} gtest gmock pthread)
