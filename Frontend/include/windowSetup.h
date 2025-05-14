#pragma once
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "stringResources.h"

GLFWwindow* SetWindow();
void RenderWindow(GLFWwindow* window);
void CloseWindow(GLFWwindow* window);
