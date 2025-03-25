cmake_minimum_required(VERSION 3.12)
project(FunctionReader)

enable_testing()

include_directories(
    ${CMAKE_SOURCE_DIR}/FunctionReader/include
    ${CMAKE_SOURCE_DIR}/Points/include
)

add_executable(${PROJECT_NAME}.tests tests/main.cpp)
add_executable(${PROJECT_NAME} src/StringDecode.cpp)

target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread point)
target_link_libraries(${PROJECT_NAME} point)
