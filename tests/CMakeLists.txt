cmake_minimum_required(VERSION 3.12)

set(SOLVER_TEST_PATH src/solverTests/)

include_directories(
    ${FUNCTION_DIR}/include
    ${SOLVER_DIR}/include
    ${POINT_DIR}/include
)

set(SOLVER_TEST_SRC "src/solverTesting.cpp"
                    "${SOLVER_TEST_PATH}/SimpleTests.cpp"
                    "${SOLVER_TEST_PATH}/MiddleTests.cpp"
                    "${SOLVER_TEST_PATH}/ExeptionTests.cpp"
                    "${SOLVER_TEST_PATH}/DiffTests.cpp")
set(POINT_TEST_SRC  "src/pointsTesting.cpp"
                    "src/solverTesting.cpp")
set(FUNC_TEST_SRC   "src/functionReaderTesting.cpp"
                    "src/solverTesting.cpp")

add_executable(solver.tests ${SOLVER_TEST_SRC})
add_executable(points.tests ${POINT_TEST_SRC})
add_executable(functionReader.tests ${FUNC_TEST_SRC})
add_executable(all.tests ${SOLVER_TEST_SRC} ${FUNC_TEST_SRC} ${POINT_TEST_SRC})
target_link_libraries(solver.tests  gtest gmock pthread solver )
target_link_libraries(points.tests gtest gmock pthread solver)
target_link_libraries(functionReader.tests gtest gmock pthread solver)
target_link_libraries(all.tests  gtest gmock pthread solver )
