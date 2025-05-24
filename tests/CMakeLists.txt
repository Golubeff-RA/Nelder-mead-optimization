cmake_minimum_required(VERSION 3.12)

set(SOLVER_TEST_PATH src/solverTests/)

include_directories(
    ${FUNCTION_DIR}/include
    ${SOLVER_DIR}/include
    ${POINT_DIR}/include
)

add_executable(solver.tests ${SOLVER_TEST_PATH}/solverTesting.cpp ${SOLVER_TEST_PATH}/SimpleTests.cpp ${SOLVER_TEST_PATH}/MiddleTests.cpp ${SOLVER_TEST_PATH}/ExeptionTests.cpp)
add_executable(points.tests src/pointsTesting.cpp)
add_executable(functionReader.tests src/functionReaderTesting.cpp)
add_executable(logger.tests src/loggerTesting.cpp)
target_link_libraries(solver.tests  gtest gmock pthread solver )
target_link_libraries(points.tests gtest gmock pthread solver)
target_link_libraries(functionReader.tests gtest gmock pthread solver) #${POINT_LIB})
target_link_libraries(logger.tests gtest gmock)

