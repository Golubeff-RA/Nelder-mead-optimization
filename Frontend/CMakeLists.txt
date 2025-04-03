cmake_minimum_required(VERSION 3.10)
project(FrontendImGui)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

#if(NOT OpenGL_FOUND OR NOT glfw3_FOUND)
 #   message(FATAL_ERROR "Необходимые библиотеки (OpenGL и GLFW) не найдены.")
#endif()

#find_library(FUNC_LIB NAMES function_parser HINTS ${CMAKE_SOURCE_DIR}/build/FunctionReader PATH_SUFFIXES lib lib64)

#if(NOT FUNC_LIB)
#    message(FATAL_ERROR "Could not find the func library.  Please set the HINTS variable in CMakeLists.txt.")
#endif()

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Frontend/imgui)
set(IMGUI_DIR_BACK ${CMAKE_SOURCE_DIR}/Frontend/imgui/backends)
set(POINT_DIR ${CMAKE_SOURCE_DIR}/Points)
set(SOLVER_DIR ${CMAKE_SOURCE_DIR}/NelderMeadSolver)
set(FUNCTION_DIR ${CMAKE_SOURCE_DIR}/FunctionReader)
set(FRONTEND_DIR ${CMAKE_SOURCE_DIR}/Frontend)
set(FONT_PATH "${IMGUI_DIR}/misc/fonts/DroidSans.ttf")

add_definitions(-DFONT_PATH=\"${FONT_PATH}\")

include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR_BACK}
    ${POINT_DIR}/include
    ${SOLVER_DIR}/include
    ${FUNCTION_DIR}/include
    ${FRONTEND_DIR}/include
)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(app STATIC
    ${FRONTEND_DIR}/src/windowSetup.cpp
    ${FRONTEND_DIR}/src/stringResources.cpp
    ${FRONTEND_DIR}/src/graphics.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} app imgui glfw ${OPENGL_LIBRARIES} GL dl point function_parser solver)
    

# Укажите флаги компиляции для ImGui (если необходимо)
target_compile_definitions(imgui PUBLIC
    IMGUI_IMPL_OPENGL_LOADER_GLAD # Или другая библиотека загрузки OpenGL, если вы ее используете
)