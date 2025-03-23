#include "solver.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "stringResources.h"

class AppUI {
private:
    NelderMeadSolver _solver;
    char _printFunction[128] = "";
    char _inputFunction[128] = "";
    char* _defaultString;
    Point _testPoint;
    double _testAnswer = 0;
    std::list<Log> _logs = std::list<Log>();
    bool _printPoint = false;
    bool _printDefault = false;

    void printPoint(const Point& point) {
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

    void readFunction() {
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

    void clearFunction() {
        strcpy(_printFunction, "");
        _printPoint = false;
        _printDefault = false;
        _logs.clear();
    }

public:
    AppUI(char* defaultString, Point testPoint)
        : _defaultString{defaultString}, _testPoint{testPoint} {
    }

    AppUI() : _testPoint{Point{std::vector<double>{1, 2, 3, 4}}} {
        _defaultString = new char[strlen(stringRes::read_function_string) + 1];
        strcpy(_defaultString, stringRes::read_function_string);
    }

    ~AppUI() {
        delete[] _defaultString;
    }

    void initFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void showIputWindow() {
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

    void showOutputWindow() {
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
};