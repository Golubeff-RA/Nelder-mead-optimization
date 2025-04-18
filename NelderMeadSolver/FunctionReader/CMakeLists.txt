cmake_minimum_required(VERSION 3.12)
project(FunctionReader)

enable_testing()

set(FUNC_DIR ${FUNCTION_DIR}/src)

include_directories(
    ${FUNCTION_DIR}/include
    ${POINT_DIR}/include
)

set (FUNC_PARSER
    ${FUNC_DIR}/algebra.cpp
    ${FUNC_DIR}/expression_parse.cpp
    ${FUNC_DIR}/function.cpp
    ${FUNC_DIR}/post_string_calculater.cpp
    ${FUNC_DIR}/post_string_transfer.cpp
)

add_library(function_parser SHARED
    ${POINT_DIR}/src/constructors.cpp
    ${POINT_DIR}/src/operators.cpp
    ${POINT_DIR}/src/measure.cpp
    ${FUNC_DIR}/algebra.cpp
    ${FUNC_DIR}/expression_parse.cpp
    ${FUNC_DIR}/function.cpp
    ${FUNC_DIR}/post_string_calculater.cpp
    ${FUNC_DIR}/post_string_transfer.cpp
)


add_executable(${PROJECT_NAME} src/StringDecode.cpp ${FUNC_PARSER})

target_link_libraries(${PROJECT_NAME} PUBLIC point) #${POINT_LIB})