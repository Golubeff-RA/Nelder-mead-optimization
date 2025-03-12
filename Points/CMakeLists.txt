cmake_minimum_required(VERSION 3.12)
project(Points)

enable_testing()
add_executable(${PROJECT_NAME}.tests tests/pointsTesting.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/Points/include)
target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread)