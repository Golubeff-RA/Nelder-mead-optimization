#include "graphics.h"
#include "windowSetup.h"

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = setWindow();
    if (window == nullptr) {
        return 1;
    }

    ImGui_ImplOpenGL3_Init("#version 130");
    AppUI app;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        app.initFrame();
        app.showIputWindow();
        app.showSettingsWindow();

        renderWindow(window);
    }
    
    closeWindow(window);
    return 0;
}
