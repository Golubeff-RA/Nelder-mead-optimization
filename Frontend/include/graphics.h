#pragma once
#include "solver.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "stringResources.h"

class AppUI {
private:
    NelderMeadSolver _solver{10e-5, 100};
    char _readedFunction[128] = "";
    char _inputFunction[128] = "";
    char* _defaultString;
    Point _startPoint = Point{{0}};
    std::list<Log> _logs = std::list<Log>();
    bool _printFunction = false;
    bool _optimizeFunction = false;
    bool _printDefault = false;
    bool _showSettings = false;
    bool _showLogs = false;
    double _answer = 0;
    float _error = 0.001;
    int _iterations = 100;
    size_t _dimensions = 0;

    void printPoint(const Point& point);
    void readFunction();
    void optimizeFunction();
    void clearFunction();

public:
    AppUI(char* defaultString);
    AppUI();

    ~AppUI();

    void initFrame();
    void showIputWindow();
    void showOutputWindow();
    void showSettingsWindow();
    bool isExpressionCorrect(std::string expression);
};