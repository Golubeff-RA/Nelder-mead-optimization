#include "graphics.h"

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
    ImGui::Begin(stringRes::input_window_string);

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

    if (_showSettings)
        showSettingsWindow();

    if (_optimizeFunction)
        showOutputWindow();

    ImGui::End();
}

void AppUI::showOutputWindow() {
    ImGui::Begin(stringRes::output_window_string);
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
}

void AppUI::showSettingsWindow() {
    ImGui::Begin(stringRes::settings_window_string);
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
        std::string id = "##" + std::to_string(i);
        ImGui::InputDouble(id.c_str(), &(_startPoint[i]));
        ImGui::SameLine();
    }
    ImGui::Text("%s", stringRes::start_point_string);

    ImGui::Text("%s %f", stringRes::saved_error_string, _error);
    ImGui::Text("%s %d", stringRes::saved_iterations_string, _iterations);
    if (ImGui::Button(stringRes::close_button_string))
        _showSettings = false;
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
    _optimizeFunction = false;
    _showSettings = false;
    try {
        strcpy(_readedFunction, _inputFunction);
        Function func(_inputFunction);
        func.Calculate(_startPoint);
        _printFunction = true;
        _dimensions = _solver.CountDim(_inputFunction);
        std::vector<double> p;
        for (size_t i = 0; i < _dimensions; i++)
            p.push_back(0);
        _startPoint = Point{p};
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        _printFunction = false;
        std::ostringstream errorStr;
        errorStr << stringRes::invalid_input_string << e.what();
        strcpy(_readedFunction, errorStr.str().c_str());
    }
}

void AppUI::optimizeFunction() {
    if (ImGui::Button(stringRes::optimize_button_string)) {
        _solver.eps_ = _error;
        _solver.epoch_ = _iterations;
        _answer = _solver.Optimize(_inputFunction, _startPoint);
        _logs = _solver.GetLogs(_inputFunction);
        _optimizeFunction = true;
    }
    ImGui::SameLine();
    if (ImGui::Button(stringRes::settings_button_string))
        _showSettings = true;
    ImGui::SameLine();
    ImGui::Checkbox(stringRes::show_logs_checkbox, &_showLogs);
}

void AppUI::clearFunction() {
    strcpy(_readedFunction, "");
    strcpy(_inputFunction, "");
    _printFunction = false;
    _optimizeFunction = false;
    _printDefault = false;
    _showSettings = false;
    _logs.clear();
}