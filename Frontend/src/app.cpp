

#include "app.h"

void glfwerror__callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void AppUI::Run() {
    glfwSetErrorCallback(glfwerror__callback);
    if (!glfwInit()) {
        exit(1);
    }

    GLFWwindow* window = SetWindow();
    if (window == nullptr) {
        exit(1);
    }

    ImGui_ImplOpenGL3_Init("#version 130");

    // установка начальных позиций и размеров
    {
        InitFrame_();
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({750, 250});
        ShowInputWindow_();
        ImGui::SetNextWindowPos({0, 250});
        ImGui::SetNextWindowSize({750, 450});
        ShowSettingsWindow_();
        RenderWindow(window);
    }

    // основной цикл приложения
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            continue;
        }

        InitFrame_();
        ShowInputWindow_();
        ShowSettingsWindow_();
        RenderWindow(window);
    }

    CloseWindow(window);
}

void AppUI::InitFrame_() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void AppUI::ShowInputWindow_() {
    ImGui::Begin(stringRes::input_window_string);
    ImGui::Text("%s", stringRes::measure_string);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(strlen(input_function_) * 10 + 50);
    ImGui::InputText(stringRes::input_function_string, input_function_, 128);

    if (ImGui::Button(stringRes::read_button_string))
        ReadFunction_();

    ImGui::SameLine();
    if (ImGui::Button(stringRes::clear_button_string))
        ClearFunction_();

    ImGui::Text("%s %s", print_default_ ? stringRes::read_function_string : "", readed_function_);
    if (print_function_)
        OptimizeFunction_();

    if (optimize_function_)
        ShowOutputWindow_();

    ImGui::End();
}

void AppUI::ShowOutputWindow_() {
    const auto& logs = logger->GetLogs(&solver_);
    ImGui::Begin(stringRes::output_window_string);
    int iter = 1;
    if (show_logs_) {
        for (const auto& log : logs) {
            ImGui::Text("%d) ", iter);
            ImGui::SameLine();
            ImGui::Text("%s %lf", stringRes::measure_string, log.func_val);
            PrintPoint_(log.best_point);
            ++iter;
        }
    }
    ImGui::Text("%s\n%s %lf", stringRes::answer_string, stringRes::measure_string, answer_);
    ImGui::Text("%s\n", stringRes::argmin);
    ImGui::SameLine();
    PrintPoint_(logs.back().best_point);
    ImGui::End();

    std::vector<float> iterations(logs.size());
    std::vector<float> func_vals(logs.size());
    size_t idx = 0;
    for (const auto& log : logs) {
        iterations[idx] = static_cast<float>(idx);
        func_vals[idx] = static_cast<float>(log.func_val);
        idx++;
    }

    ImGui::Begin(stringRes::graphic_window_string);
    if (ImPlot::BeginPlot(stringRes::function_graphic_string, ImVec2(-1, -1))) {
        ImPlot::PlotLine(stringRes::q_from_X_string, iterations.data(), func_vals.data(),
                         logs.size());
        ImPlot::EndPlot();
    }
    ImGui::End();
}

void AppUI::ShowSettingsWindow_() {
    ImGui::Begin(stringRes::settings_window_string);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 250);
    ImGui::InputFloat(stringRes::solving_error_string, &error_);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 15);
    ImGui::SliderFloat("##se", &error_, 0.0f, 1.0f);

    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 270);
    ImGui::InputInt(stringRes::max_iterations_string, &iterations_);
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 15);
    ImGui::SliderInt("##mi", &iterations_, 0, 1000);
    for (size_t i = 0; i < dimensions_; i++) {
        ImGui::SetNextItemWidth(150);
        ImGui::InputDouble(std::string("#" + std::to_string(i + 1)).c_str(), &(start_point_[i]));
        if ((i + 1) % 4 != 0) {
            ImGui::SameLine();
        }
    }
    ImGui::Text("%s", stringRes::start_point_string);
    ImGui::Text("%s %f", stringRes::saved_error_string, error_);
    ImGui::Text("%s %d", stringRes::saved_iterations_string, iterations_);
    ImGui::End();
}

void AppUI::PrintPoint_(const Point& point) {
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

bool AppUI::IsExprCorrect_(std::string expression) {
    auto words_begin = std::sregex_iterator(expression.begin(), expression.end(), check_fn_regex_);
    auto words_end = std::sregex_iterator();
    std::string reconstructed;
    for (auto it = words_begin; it != words_end; ++it) {
        reconstructed += it->str();
    }

    return reconstructed == expression;
}

void AppUI::ReadFunction_() {
    print_default_ = true;
    ImPlot::DestroyContext();
    optimize_function_ = false;
    strcpy(readed_function_, input_function_);
    if (IsExprCorrect_(readed_function_)) {
        try {
            FR::Function func(readed_function_);
            print_function_ = true;
            dimensions_ = solver_.CountDim(readed_function_);
            start_point_ = Point(dimensions_);
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            print_function_ = false;
            std::ostringstream errorStr;
            errorStr << stringRes::invalid_input_string << e.what();
            strcpy(readed_function_, errorStr.str().c_str());
        }
    } else {
        print_function_ = false;
        strcpy(readed_function_, "invalid expression");
    }
}

void AppUI::OptimizeFunction_() {
    if (ImGui::Button(stringRes::optimize_button_string)) {
        try {
            answer_ = solver_.Optimize(
                {readed_function_, static_cast<size_t>(iterations_), error_, start_point_});
            ImPlot::CreateContext();
            optimize_function_ = true;
        } catch (const std::runtime_error& e) {
            ImPlot::DestroyContext();
            optimize_function_ = false;
            std::cerr << e.what() << '\n';
            std::ostringstream errorStr;
            errorStr << stringRes::invalid_input_string << e.what();
            strcpy(readed_function_, errorStr.str().c_str());
        }
    }
    ImGui::SameLine();
    ImGui::Checkbox(stringRes::show_logs_checkbox, &show_logs_);
}

void AppUI::ClearFunction_() {
    ImPlot::DestroyContext();
    strcpy(readed_function_, "");
    strcpy(input_function_, "");
    optimize_function_ = false;
    print_function_ = false;
    print_default_ = false;
}