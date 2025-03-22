#include "graphics.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

char read_function_string[15] = "Function read:";
char invalid_input_string[] = "invalid input\nError: ";
char measure_string[] = "Q(X)=";
char input_function_string[] = "<- input function";
char read_button_string[] = "Read";
char clear_button_string[] = "Clear";
char input_window_string[] = "Input window";
char output_window_string[] = "Output window";
char function_value_string[] = "Test value:";

AppUI::AppUI(char* defaultString, Point testPoint)
    : _defaultString{defaultString}, _testPoint{testPoint} {
}

AppUI::AppUI()
    : _defaultString{read_function_string}, _testPoint{Point{std::vector<double>{1, 2, 3, 4}}} {
}

AppUI::~AppUI() {
}

void AppUI::printPoint(const Point& point) {
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

void AppUI::readFunction() {
    try {
        strcpy(_printFunction, _inputFunction);
        strcpy(_defaultString, read_function_string);
        _logs = _solver.GetLogs(_inputFunction);
        Function func(_inputFunction);
        _testAnswer = func.Calculate(_testPoint);
        _printPoint = true;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        _printPoint = false;
        std::ostringstream errorStr;
        errorStr << invalid_input_string << e.what();
        strcpy(_printFunction, errorStr.str().c_str());
    }
}

void AppUI::clearFunction() {
    strcpy(_printFunction, "");
    strcpy(_defaultString, "");
    _printPoint = false;
    _logs.clear();
}

void AppUI::initFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void AppUI::showIputWindow() {
    ImGui::Begin(input_window_string);

    ImGui::Text("%s", measure_string);
    ImGui::SameLine();
    ImGui::InputText(input_function_string, _inputFunction, 128);

    if (ImGui::Button(read_button_string)) {
        readFunction();
    }
    ImGui::SameLine();
    if (ImGui::Button(clear_button_string))
        clearFunction();

    ImGui::Text("%s %s", _defaultString, _printFunction);

    if (!_logs.empty() && _printPoint)
        showOutputWindow();
    ImGui::End();
}

void AppUI::showOutputWindow() {
    ImGui::Begin(output_window_string);
    ImGui::Text("Test logs:");
    for (Log log : _logs) {
        ImGui::Text("log:");
        for (Point p : log.points)
            printPoint(p);
        ImGui::Text("%s %lf", measure_string, log.func_val);
    }
    ImGui::Text("%s", function_value_string);
    printPoint(_testPoint);
    ImGui::Text("%s %lf", measure_string, _testAnswer);
    ImGui::End();
}