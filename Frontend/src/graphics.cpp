#include "graphics.h"

AppUI::AppUI(char* defaultString, Point testPoint) : 
    _defaultString{defaultString}, _testPoint{testPoint} {
    }
AppUI::AppUI() : _testPoint{Point{std::vector<double>{1, 2, 3, 4}}} {
     _defaultString = new char[strlen(stringRes::read_function_string) + 1];
    strcpy(_defaultString, stringRes::read_function_string);
}

AppUI::~AppUI() {
    delete[] _defaultString;
}

void AppUI::initFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void AppUI::showIputWindow() {
    ImGui::Begin(stringRes::input_window_string);

    ImGui::Text("%s", stringRes::measure_string);
    ImGui::SameLine();
    ImGui::InputText(stringRes::input_function_string, _inputFunction, 128);

    if (ImGui::Button(stringRes::read_button_string))
        readFunction();

    ImGui::SameLine();
    if (ImGui::Button(stringRes::clear_button_string))
        clearFunction();

    ImGui::Text("%s %s", _printDefault ? _defaultString : "", _printFunction);
    if (!_logs.empty() && _printPoint)
        showOutputWindow();

    ImGui::End();
}

void AppUI::showOutputWindow() {
    ImGui::Begin(stringRes::output_window_string);
    ImGui::Text("Test logs:");
    for (Log log : _logs) {
        ImGui::Text("log:");
        for (Point p : log.points)
            printPoint(p);
        ImGui::Text("%s %lf", stringRes::measure_string, log.func_val);
    }
    ImGui::Text("%s", stringRes::function_value_string);
    printPoint(_testPoint);
    ImGui::Text("%s %lf", stringRes::measure_string, _testAnswer);
    ImGui::End();
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
    _printDefault = true;
    try {
        strcpy(_printFunction, _inputFunction);
        _logs = _solver.GetLogs("x1 + x2");
        Function func(_inputFunction);
        _testAnswer = func.Calculate(_testPoint);
        _printPoint = true;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        _printPoint = false;
        std::ostringstream errorStr;
        errorStr << stringRes::invalid_input_string << e.what();
        strcpy(_printFunction, errorStr.str().c_str());
    }
}

void AppUI::clearFunction() {
    strcpy(_printFunction, "");
    _printPoint = false;
    _printDefault = false;
    _logs.clear();
}