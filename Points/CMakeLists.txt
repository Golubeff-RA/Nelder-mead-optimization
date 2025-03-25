cmake_minimum_required(VERSION 3.12)
project(Points)

enable_testing()



add_executable(${PROJECT_NAME}.tests tests/pointsTesting.cpp src/constructors.cpp src/operators.cpp src/measure.cpp)
add_executable(${PROJECT_NAME} src/main.cpp src/constructors.cpp src/operators.cpp src/measure.cpp)

include_directories(${CMAKE_SOURCE_DIR}/Points/include)
target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread)