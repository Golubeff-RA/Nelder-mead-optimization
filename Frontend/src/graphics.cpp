#include "graphics.h"

#include <regex>

#include "implot.h"

AppUI::AppUI(char* defaultString) : _defaultString{defaultString} {
}
AppUI::AppUI() {
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
    ImGui::Begin(stringRes::input_window_string, nullptr, ImGuiWindowFlags_NoMove);

    ImGui::Text("%s", stringRes::measure_string);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(strlen(_inputFunction) * 10 + 50);
    ImGui::InputText(stringRes::input_function_string, _inputFunction, 128);

    if (ImGui::Button(stringRes::read_button_string))
        readFunction();

    ImGui::SameLine();
    if (ImGui::Button(stringRes::clear_button_string))
        clearFunction();

    ImGui::Text("%s %s", _printDefault ? _defaultString : "", _readedFunction);
    if (_printFunction)
        optimizeFunction();

    if (_optimizeFunction)
        showOutputWindow();

    ImGui::End();
}

void AppUI::showOutputWindow() {
    ImGui::Begin(stringRes::output_window_string, nullptr, ImGuiWindowFlags_NoMove);
    int index = 1;
    if (_showLogs)
        for (Log log : _logs) {
            ImGui::Text("%d) log:", index);
            for (Point p : log.points)
                printPoint(p);
            ImGui::Text("%s %lf", stringRes::measure_string, log.func_val);
            index++;
        }
    ImGui::Text("%s\n%s %lf", stringRes::answer_string, stringRes::measure_string, _answer);
    ImGui::End();

    float* generations = new float[_logs.size()];
    float* functionValues = new float[_logs.size()];
    size_t idx = 0;
    for (const Log& log : _logs) {
        generations[idx] = static_cast<float>(idx + 1);
        functionValues[idx] = static_cast<float>(log.func_val);
        idx++;
    }

    ImGui::Begin(stringRes::graphic_window_string, nullptr, ImGuiWindowFlags_NoMove);
    if (ImPlot::BeginPlot(stringRes::function_graphic_string, ImVec2(-1, -1))) {
        ImPlot::PlotLine(stringRes::q_from_X_string, generations, functionValues, _logs.size());
        ImPlot::EndPlot();
    }
    ImGui::End();

    delete[] generations;
    delete[] functionValues;
}

void AppUI::showSettingsWindow() {
    ImGui::Begin(stringRes::settings_window_string, nullptr, ImGuiWindowFlags_NoMove);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 250);
    ImGui::InputFloat(stringRes::solving_error_string, &_error);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 15);
    ImGui::SliderFloat("##se", &_error, 0.0f, 1.0f);

    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 270);
    ImGui::InputInt(stringRes::max_iterations_string, &_iterations);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 15);
    ImGui::SliderInt("##mi", &_iterations, 0, 1000);
    for (size_t i = 0; i < _dimensions; i++) {
        ImGui::SetNextItemWidth(150);
        ImGui::InputDouble(std::string("#" + std::to_string(i + 1)).c_str(), &(_startPoint[i]));
        if ((i + 1) % 4 != 0) {
            ImGui::SameLine();
        }
    }
    ImGui::Text("%s", stringRes::start_point_string);
    ImGui::Text("%s %f", stringRes::saved_error_string, _error);
    ImGui::Text("%s %d", stringRes::saved_iterations_string, _iterations);
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

bool AppUI::isExpressionCorrect(std::string expression) {
    std::regex token_regex(
        R"(\b(sin|cos|tan|ctg|ln|log2|log|sqrt|abs)\b|\bx\d+\b|[-+*/^() ]|\d+\.?\d*)",
        std::regex_constants::ECMAScript);

    auto words_begin = std::sregex_iterator(expression.begin(), expression.end(), token_regex);
    auto words_end = std::sregex_iterator();

    std::string reconstructed;
    for (auto it = words_begin; it != words_end; ++it) {
        reconstructed += it->str();
    }

    return reconstructed == expression;
}

void AppUI::readFunction() {
    _printDefault = true;
    ImPlot::DestroyContext();
    _optimizeFunction = false;
    strcpy(_readedFunction, _inputFunction);
    std::cout << isExpressionCorrect(_inputFunction);
    if (isExpressionCorrect(_inputFunction)) {
        try {
            Function func(_inputFunction);
            _printFunction = true;
            _dimensions = _solver.CountDim(_inputFunction);
            _startPoint = Point(_dimensions);

        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            _printFunction = false;
            std::ostringstream errorStr;
            errorStr << stringRes::invalid_input_string << e.what();
            strcpy(_readedFunction, errorStr.str().c_str());
        }
    } else {
        _printFunction = false;
        strcpy(_readedFunction, "invalid expression");
    }
}

void AppUI::optimizeFunction() {
    if (ImGui::Button(stringRes::optimize_button_string)) {
        try {
            _solver.eps() = _error;
            _solver.epoch() = _iterations;
            _answer = _solver.Optimize(_inputFunction, _startPoint);
            _logs = _solver.GetLogs(_inputFunction);
            ImPlot::CreateContext();
            _optimizeFunction = true;
        } catch (const std::runtime_error& e) {
            ImPlot::DestroyContext();
            _optimizeFunction = false;
            std::cerr << e.what() << '\n';
            std::ostringstream errorStr;
            errorStr << stringRes::invalid_input_string << e.what();
            strcpy(_readedFunction, errorStr.str().c_str());
        }
    }
    ImGui::SameLine();
    ImGui::Checkbox(stringRes::show_logs_checkbox, &_showLogs);
}

void AppUI::clearFunction() {
    strcpy(_readedFunction, "");
    strcpy(_inputFunction, "");
    _printFunction = false;
    ImPlot::DestroyContext();
    _optimizeFunction = false;
    _printDefault = false;
    _logs.clear();
}