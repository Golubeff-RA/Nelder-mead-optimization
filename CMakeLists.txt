cmake_minimum_required(VERSION 3.5.0)
project (Nelder-Mead-Optimisation)

set (CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_CXX_FLAGS "-Wall -Werror -Wsign-compare")

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all -O2"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

set(CMAKE_CXX_FLAGS_REL "-O2 -DNDEBUG"
    CACHE STRING "Compiler flags for the release version"
    FORCE)

message("General compiler flags: " ${CMAKE_CXX_FLAGS})
message("Debug build compiler flags: " ${CMAKE_CXX_FLAGS_DEBUG})
message("ASAN build compiler flags: " ${CMAKE_CXX_FLAGS_ASAN})
message("Release build compiler flags: " ${CMAKE_CXX_FLAGS_REL})

add_subdirectory(FunctionReader)
add_subdirectory(NelderMeadSolver)
add_subdirectory(Frontend)
add_subdirectory(Points)