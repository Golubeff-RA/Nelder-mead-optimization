cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

add_subdirectory(FunctionReader)

#include_directories(${POINT_DIR}/include)

add_library(point STATIC
    ${POINT_DIR}/src/constructors.cpp
    ${POINT_DIR}/src/operators.cpp
    ${POINT_DIR}/src/measure.cpp
    )

enable_testing()

add_library(solver SHARED
    ${SOLVER_DIR}/src/solver.cpp
)

add_executable(${PROJECT_NAME} 
    src/playground.cpp 
)

include_directories(
    ${FUNCTION_DIR}/include
    ${SOLVER_DIR}/include
    ${POINT_DIR}/include
)

target_link_libraries(${PROJECT_NAME} function_parser)