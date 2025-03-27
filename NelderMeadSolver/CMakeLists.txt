cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

enable_testing()

set(POINT_DIR ${CMAKE_SOURCE_DIR}/Points)
set(FUNCTION_DIR ${CMAKE_SOURCE_DIR}/FunctionReader)
set(SOLVER_DIR ${CMAKE_SOURCE_DIR}/NelderMeadSolver)

find_library(FUNC_LIB NAMES function_parser HINTS ${CMAKE_SOURCE_DIR}/build/FunctionReader PATH_SUFFIXES lib lib64)

#if(NOT FUNC_LIB)
 #   message(FATAL_ERROR "Could not find the point library.  Please set the HINTS variable in CMakeLists.txt.")
#else()
 #   message(STATUS "Found point library at: ${POINT_LIB}")
#endif()

add_library(solver STATIC
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
target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread ${FUNC_LIB})
target_link_libraries(${PROJECT_NAME} point ${FUNC_LIB})