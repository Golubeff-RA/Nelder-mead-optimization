#pragma once
#include <regex>

#include "implot.h"
#include "solver.h"
#include "stringResources.h"
#include "windowSetup.h"

class AppUI {
private:
    // точка для старта метода
    Point start_point_ = Point(0);
    // оптимизатор
    NelderMeadSolver solver_;

    char readed_function_[128] = "";
    char input_function_[128] = "";
    
    bool optimize_function_ = false;
    bool print_function_ = false;
    bool print_default_ = false;
    bool show_logs_ = false;

    double answer_ = 0;
    float error_ = 1e-5;
    int iterations_ = 100;
    size_t dimensions_ = 0;
    std::regex check_fn_regex_ =
        std::regex(R"(\b(sin|cos|tan|ctg|ln|log2|log|sqrt|abs)\b|\bx\d+\b|[-+*/^() ]|\d+\.?\d*)",
                   std::regex_constants::ECMAScript);

    bool IsExprCorrect_(std::string expression);
    void PrintPoint_(const Point& point);
    void OptimizeFunction_();
    void ClearFunction_();
    void ReadFunction_();

    // функции для отрисовки окон
    void InitFrame_();
    void ShowInputWindow_();
    void ShowOutputWindow_();
    void ShowSettingsWindow_();
public:
    void Run();
};
