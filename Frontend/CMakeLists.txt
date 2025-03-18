cmake_minimum_required(VERSION 3.10)
project(FrontendImGui)

set(CMAKE_CXX_STANDARD 17)  # Или более поздняя версия, если требуется

# Включите модуль FindOpenGL для поиска OpenGL
find_package(OpenGL REQUIRED)

# Включите модуль FindGLFW для поиска GLFW
find_package(glfw3 REQUIRED)

if(NOT OpenGL_FOUND OR NOT glfw3_FOUND)
    message(FATAL_ERROR "Необходимые библиотеки (OpenGL и GLFW) не найдены.")
endif()

# Путь к исходникам ImGui. Укажите реальный путь!
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Frontend/imgui)
set(IMGUI_DIR_BACK ${CMAKE_SOURCE_DIR}/Frontend/imgui/backends)
set(POINT_DIR ${CMAKE_SOURCE_DIR}/Points)
set(SOLVER_DIR ${CMAKE_SOURCE_DIR}/NelderMeadSolver)
set(FUNCTION_DIR ${CMAKE_SOURCE_DIR}/FunctionReader)

# Добавьте исходники ImGui
include_directories(${IMGUI_DIR} ${IMGUI_DIR_BACK} ${POINT_DIR}/include ${SOLVER_DIR}/include ${FUNCTION_DIR}/include)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp  # Опционально, для демо-примера
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(points STATIC
    ${POINT_DIR}/src/constructors.cpp
    ${POINT_DIR}/src/operators.cpp
)

# Добавьте заголовочные файлы ImGui в пути поиска
include_directories(${IMGUI_DIR}, )

# Добавьте свой исходный файл
add_executable(FrontendImGui main.cpp)

# Свяжите вашу программу с ImGui, GLFW и OpenGL
target_link_libraries(FrontendImGui imgui glfw ${OPENGL_LIBRARIES} points)


# Укажите флаги компиляции для ImGui (если необходимо)
target_compile_definitions(imgui PUBLIC
    IMGUI_IMPL_OPENGL_LOADER_GLAD # Или другая библиотека загрузки OpenGL, если вы ее используете
)

# Включите поддержку C++11/14/17 для ImGui (если требуется)
target_compile_features(imgui PUBLIC cxx_std_11)

# Укажите где искать библиотеку ImGui. Не нужно если исходники рядом с main.cpp
#link_directories(${IMGUI_DIR})