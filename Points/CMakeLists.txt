cmake_minimum_required(VERSION 3.12)
project(Points)

enable_testing()

set(POINTS_DIR ${CMAKE_SOURCE_DIR}/Points)

include_directories(${POINTS_DIR}/include)

add_library(point STATIC
    ${POINTS_DIR}/src/constructors.cpp
    ${POINTS_DIR}/src/operators.cpp
    ${POINTS_DIR}/src/measure.cpp
    )
    
add_executable(${PROJECT_NAME}.tests tests/pointsTesting.cpp)

target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread point)