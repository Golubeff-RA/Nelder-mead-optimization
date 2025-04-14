cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

add_subdirectory(FunctionReader)

add_library(point STATIC
    ${POINT_DIR}/src/constructors.cpp
    ${POINT_DIR}/src/operators.cpp
    ${POINT_DIR}/src/measure.cpp
    )

enable_testing()

add_library(solver SHARED
    ${POINT_DIR}/src/constructors.cpp
    ${POINT_DIR}/src/operators.cpp
    ${POINT_DIR}/src/measure.cpp
    ${SOLVER_DIR}/src/solver.cpp
    ${SOLVER_DIR}/src/solver_utils.cpp
)

add_executable(${PROJECT_NAME} 
    src/playground.cpp 
    ${SOLVER_DIR}/src/solver.cpp
    ${SOLVER_DIR}/src/solver_utils.cpp
)

include_directories(
    ${FUNCTION_DIR}/include
    ${SOLVER_DIR}/include
    ${POINT_DIR}/include
)

target_link_libraries(${PROJECT_NAME} function_parser)