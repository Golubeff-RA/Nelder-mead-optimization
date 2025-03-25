cmake_minimum_required(VERSION 3.12)
project(FunctionReader)

enable_testing()

set(FUNC_DIR ${CMAKE_SOURCE_DIR}/FunctionReader/src)

include_directories(
    ${CMAKE_SOURCE_DIR}/FunctionReader/include
    ${CMAKE_SOURCE_DIR}/Points/include
)

#find_library(POINT_LIB NAMES point HINTS ${CMAKE_SOURCE_DIR}/build/Points PATH_SUFFIXES lib lib64)

#if(NOT POINT_LIB)
#    message(FATAL_ERROR "Could not find the point library.  Please set the HINTS variable in CMakeLists.txt.")
#endif()

set (FUNC_PARSER
    ${FUNC_DIR}/algebra.cpp
    ${FUNC_DIR}/expression_parse.cpp
    ${FUNC_DIR}/function.cpp
    ${FUNC_DIR}/post_string_calculater.cpp
    ${FUNC_DIR}/post_string_transfer.cpp
)

set(POINTS_DIR ${CMAKE_SOURCE_DIR}/Points)
add_library(function_parser STATIC
    ${POINTS_DIR}/src/constructors.cpp
    ${POINTS_DIR}/src/operators.cpp
    ${POINTS_DIR}/src/measure.cpp
    ${FUNC_DIR}/algebra.cpp
    ${FUNC_DIR}/expression_parse.cpp
    ${FUNC_DIR}/function.cpp
    ${FUNC_DIR}/post_string_calculater.cpp
    ${FUNC_DIR}/post_string_transfer.cpp
)

add_executable(${PROJECT_NAME}.tests tests/main.cpp ${FUNC_PARSER})
add_executable(${PROJECT_NAME} src/StringDecode.cpp ${FUNC_PARSER})

target_link_libraries(${PROJECT_NAME}.tests gtest gmock pthread) #${POINT_LIB})
target_link_libraries(${PROJECT_NAME}) #${POINT_LIB})
