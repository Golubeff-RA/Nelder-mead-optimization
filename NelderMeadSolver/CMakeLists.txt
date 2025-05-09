cmake_minimum_required(VERSION 3.12)
project(NelderMeadSolver)

add_subdirectory(FunctionReader)

add_library(solver SHARED
    ${SOLVER_DIR}/src/solver.cpp
    ${SOLVER_DIR}/src/solver_utils.cpp
)

add_library(point SHARED
    ${POINT_DIR}/src/constructors.cpp
    ${POINT_DIR}/src/operators.cpp
    ${POINT_DIR}/src/measure.cpp
)

target_link_libraries(solver PUBLIC function_parser point)

add_executable(${PROJECT_NAME} src/playground.cpp)

include_directories(
    ${FUNCTION_DIR}/include
    ${SOLVER_DIR}/include
    ${POINT_DIR}/include
)

target_link_libraries(${PROJECT_NAME} solver)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:function_parser>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:function_parser>"
)