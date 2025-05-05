cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

add_subdirectory(FunctionReader)

add_library(solver SHARED
    ${SOLVER_DIR}/src/solver.cpp
    ${SOLVER_DIR}/src/solver_utils.cpp
)

target_link_libraries(solver PUBLIC function_parser)

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