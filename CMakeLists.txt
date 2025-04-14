cmake_minimum_required(VERSION 3.5.0)

project (Nelder-Mead-Optimisation)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE "GLVND")
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Frontend/imgui)
set(IMGUI_DIR_BACK ${CMAKE_SOURCE_DIR}/Frontend/imgui/backends)
set(SOLVER_DIR ${CMAKE_SOURCE_DIR}/NelderMeadSolver)
set(POINT_DIR ${SOLVER_DIR}/Points)
set(FUNCTION_DIR ${SOLVER_DIR}/FunctionReader)
set(FRONTEND_DIR ${CMAKE_SOURCE_DIR}/Frontend)
set(FONT_PATH "${IMGUI_DIR}/misc/fonts/DroidSans.ttf")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wsign-compare")

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

add_subdirectory(NelderMeadSolver)
add_subdirectory(Frontend)
add_subdirectory(tests)