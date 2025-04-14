cmake_minimum_required(VERSION 3.12)

include_directories(
    ${FUNCTION_DIR}/include
    ${SOLVER_DIR}/include
    ${POINT_DIR}/include
)

add_executable(solver.tests src/solverTesting.cpp)
add_executable(points.tests src/pointsTesting.cpp)
add_executable(functionReader.tests src/functionReaderTesting.cpp)
target_link_libraries(solver.tests  gtest gmock pthread function_parser )
target_link_libraries(points.tests gtest gmock pthread point)
target_link_libraries(functionReader.tests gtest gmock pthread function_parser) #${POINT_LIB})


