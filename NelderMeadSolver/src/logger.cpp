#include "logger.h"

namespace SLV {
std::string TimePointToStr(const TimePoint& tp) {
    auto time = std::chrono::system_clock::to_time_t(tp);
    std::tm local_time = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%d.%m.%y %H.%M.%S");
    return oss.str();
};

LoggerPtr Logger::GetLogger() {
    std::call_once(init_flag, []() { instance = std::shared_ptr<Logger>(new Logger()); });
    return instance;
}

void Logger::SaveLogs(const OptInfo& info, const std::list<Log>& logs,
                      const NelderMeadSolver* solver) {
    last_optimizations[solver] = {std::move(info), std::move(logs)};
}

void Logger::WriteHTML(const NelderMeadSolver* solver) {
    // std::cout << "Writing logs from solver" << solver << std::endl;
    if (!last_optimizations.contains(solver)) {
        return;
    }

    auto info = last_optimizations[solver].info;
    auto logs = last_optimizations[solver].logs;
    std::string filename = std::format("{}", (static_cast<const void*>(solver))) + " " +
                           TimePointToStr(ch::system_clock::now()) + " " + std::to_string(counter) +
                           " .html";

    std::ofstream out_file{subdir_path / filename};
    WriteHead_(out_file);
    WriteOptInfo_(out_file, info);
    WriteAnswer_(out_file, logs);
    WriteLogs_(out_file, logs);
    out_file.close();
    ++counter;
    UpdateIndexHtml_(subdir_path / filename, info, solver);
}

LogList Logger::GetLogs(const NelderMeadSolver* solver) {
    if (last_optimizations.contains(solver)) {
        return last_optimizations.at(solver).logs;
    }
    return {};
}

Logger::Logger() {
    std::cout << "Logger created on " << this << std::endl;
    if (!fs::exists(parent_path)) {
        fs::create_directories(parent_path);
        WriteIndexHTML_();
    }
    std::string time_str = TimePointToStr(ch::system_clock::now());
    subdir_path = parent_path / time_str;
    if (fs::create_directory(subdir_path)) {
        std::cout << "Логи будут записаны в: " << subdir_path << std::endl;
    } else {
        std::cerr << "Не удалось создать директорию для логов :(";
        exit(1);
    }
}

void Logger::UpdateIndexHtml_(fs::path new_file, const OptInfo& info,
                              const NelderMeadSolver* solver) {
    if (new_file.has_relative_path()) {
        new_file = new_file.lexically_relative(new_file.root_path() / new_file.begin()->string());
    }
    std::ofstream index_html(parent_path / "index.html", std::ios::app);
    index_html << "<li><a href=" << new_file << ">" << info.function << "</a>";
    index_html << "__Итерации: " << info.epoch << " Min мера: " << info.measure << " Точка: ";
    WritePoint_(index_html, info.start_point);
    index_html << "</li>\n";
    index_html.close();
}

void Logger::WriteIndexHTML_() {
    std::ofstream index_html(parent_path / "index.html");
    index_html << "<head><title>История оптимизаций</title> \
                   <style> body {font-family: 'Courier New', Courier, monospace;} </style></head>\n";
    index_html << "<body> <h3>История оптимизаций</h3>\n<ol>";
    index_html.close();
}

void Logger::WriteHead_(std::ostream& out) {
    out << "<head>\n"
           "<title> Q(X) #"
        << counter
        << "</title>\n"
           "<style> body {font-family: 'Courier New', Courier, monospace;} </style>\n"
           "</head>\n"
           "<body>\n";
};

void Logger::WriteOptInfo_(std::ostream& out, const OptInfo& info) {
    out << "<h3>Логи оптимизации функции Q(X) = " << info.function << "</h3>\n";
    out << "<p> MAX число итераций: " << info.epoch << "</p>\n";
    out << "<p> MIN мера симплекса: " << info.measure << "</p>\n";
    out << "<p> Стартовая точка: ";
    WritePoint_(out, info.start_point);
    out << "</p> <hr>\n";
}

void Logger::WritePoint_(std::ostream& out, const Point& p) {
    out << "(";
    for (size_t i = 0; i < p.Size(); ++i) {
        out << std::fixed << std::setw(15) << std::setprecision(6) << p[i];
        if (i != p.Size() - 1) {
            out << ", ";
        }
    }
    out << ")";
}

void Logger::WriteAnswer_(std::ostream& out, const LogList& logs) {
    out << "<h3> Ответ: ~min(Q(X))=" << logs.back().func_val << " ~argmin(Q(X)): ";
    WritePoint_(out, logs.back().best_point);
    out << "</h3><hr>\n";
}

void Logger::WriteLogs_(std::ostream& out, const LogList& logs) {
    out << "<ol>\n";
    for (const auto& log : logs) {
        out << "<pre><li> Q(X) = " << std::fixed << std::setw(15) << std::setprecision(6)
            << log.func_val << "| measure = " << std::fixed << std::setw(15) << std::setprecision(6)
            << log.measure << "| X = ";
        WritePoint_(out, log.best_point);
        out << "</li></pre>\n";
    }
    out << "</ol>\n";
}
}  // namespace SLV
