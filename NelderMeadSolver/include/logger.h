#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include "point.h"

namespace SLV {
namespace ch = std::chrono;
namespace fs = std::filesystem;

using TimePoint = std::chrono::system_clock::time_point;

class Logger;
class NelderMeadSolver;

using LoggerPtr = std::shared_ptr<Logger>;

struct Log {
    double func_val;
    double measure;
    Point best_point;
};

struct OptInfo {
    std::string function;
    size_t epoch;
    double measure;
    Point start_point;
};

using LogList = std::list<Log>;

struct Optimization {
    OptInfo info;
    LogList logs;
};

std::string TimePointToStr(const TimePoint& tp);

class Logger {
public:
    static LoggerPtr GetLogger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    LogList GetLogs(const NelderMeadSolver* solver);
    void SaveLogs(const OptInfo& info, const std::list<Log>& logs, const NelderMeadSolver* solver);
    void WriteHTML(const NelderMeadSolver* solver);

private:
    size_t counter{0};
    fs::path subdir_path;
    static LoggerPtr instance;
    static std::once_flag init_flag;
    const fs::path parent_path{"optimization_logs"};
    std::map<const NelderMeadSolver*, Optimization> last_optimizations;

    Logger();

    void WriteIndexHTML_();
    void WriteHead_(std::ostream& out);
    void WritePoint_(std::ostream& out, const Point& p);
    void WriteLogs_(std::ostream& out, const LogList& logs);
    void WriteAnswer_(std::ostream& out, const LogList& logs);
    void WriteOptInfo_(std::ostream& out, const OptInfo& info);
    void UpdateIndexHtml_(fs::path new_file, const OptInfo& info, const NelderMeadSolver* solver);
};

inline LoggerPtr Logger::instance = nullptr;
inline std::once_flag Logger::init_flag;
}  // namespace SLV
