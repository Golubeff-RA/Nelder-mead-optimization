#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <GLFW/glfw3.h>  // Will drag system OpenGL headers
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

GLFWwindow* setWindow();
void renderWindow(GLFWwindow* window);
void closeWindow(GLFWwindow* window);
