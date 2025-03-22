#include "windowSetup.h"
#include "graphics.h"
//#include "point.h"
//#include "solver.h"
//#include "graphics.h"

#define GL_SILENCE_DEPRECATION

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void PrintPoint(const Point& point) {
    ImGui::Text("(");
    ImGui::SameLine();
    for (size_t i = 0; i < point.Size(); ++i) {
        ImGui::Text("%lf", point[i]);
        ImGui::SameLine();
        if (i != point.Size() - 1) {
            ImGui::Text(";");
            ImGui::SameLine();
        }
    }
    ImGui::Text(")");
}

int main(int, char**) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    GLFWwindow* window = setWindow();
    if (window == NULL)
        return 1;

#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    NelderMeadSolver solver;
    char printFunction[128] = "";
    char defaultString[18] = "";
    char inputFunction[128] = "";
    bool printPoint = false;
    Point testPoint{std::vector<double>{1, 0, 2, 10}};
    double testAnswer = 0;
    std::list<Log> logs = std::list<Log>();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Input window");

        ImGui::Text("Q(X)=");
        ImGui::SameLine();
        ImGui::InputText("<- input function", inputFunction, 128);
        if (ImGui::Button("Read")) {
            try {
                strcpy(printFunction, inputFunction);
                strcpy(defaultString, "Function read:");
                logs = solver.GetLogs("x1 + x2");
                Function func(inputFunction);
                testAnswer = func.Calculate(testPoint);
                printPoint = true;
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << '\n';
                printPoint = false;
                std::ostringstream errorStr;
                errorStr << "invalid input\nError: " << e.what();
                strcpy(printFunction, errorStr.str().c_str());
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            strcpy(printFunction, "");
            strcpy(defaultString, "");
            printPoint = false;
            logs.clear();
        }
        ImGui::Text("%s %s", defaultString, printFunction);

        if (!logs.empty() && printPoint) {
            ImGui::Begin("Output window");
            ImGui::Text("Test logs:");
            for (Log log : logs) {
                ImGui::Text("log:");
                for (Point p : log.points)
                    PrintPoint(p);
                ImGui::Text("Q(X) = %lf", log.func_val);
            }
            ImGui::Text("Test value:");
            PrintPoint(testPoint);
            ImGui::Text("Function value = %lf", testAnswer);
            ImGui::End();
        }
        ImGui::End();

        renderWindow(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    closeWindow(window);

    return 0;
}
