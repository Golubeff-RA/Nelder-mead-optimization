#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "point.h"
#include "solver.h"

std::vector<std::string> Split(const std::string& string,
    const std::string& delimiter = " ") {
std::vector<std::string> out;

if (string.empty()) {
return out;
}

size_t lastpos1 = 0;
while (string.find(delimiter, lastpos1) != std::string::npos) {
size_t lastpos2 = string.find(delimiter, lastpos1);
out.push_back(string.substr(lastpos1, lastpos2 - lastpos1));
lastpos1 = lastpos2 + delimiter.size();
}
out.push_back(string.substr(lastpos1, string.size() - lastpos1));

return out;
}

void PrintPoint(const Point& p, std::ostream& out) {
    out << "(";
    for (size_t idx = 0; idx < p.Size(); ++idx) {
        out << p[idx];
        if (idx != p.Size() - 1) {
            out << ", ";
        }
    }
    out << ")";
}

void WriteLog(const Log& log, std::ostream& out) {
    out << log.func_val << " " << log.measure << " {";
    for (const auto& point : log.points) {
        PrintPoint(point, out);
    }
    out << "}\n";
}

// 0 - имя программы
// 1 - число итераций
// 2 - минимальный симплекс
// 3 - функция
// 4 - путь до файла логов
// 5 - стартовая точка
int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];  // Преобразование char* в std::string
        std::cout << "Аргумент " << i << ": " << arg << std::endl;
    }
    const uint32_t epoch = atoi(argv[1]);
    const double eps = atof(argv[2]);
    NelderMeadSolver solver(eps, epoch);
    const std::string func_str(argv[3]);
    std::ofstream out_file(argv[4]);
    try {
        std::vector<double> point_data;
        for (const auto& coord : Split(argv[5])) {
            point_data.push_back(atof(coord.c_str()));
        }
        solver.Optimize(func_str, Point(point_data));
    } catch (...) {
        return 1;
    }

    for (const auto& log : solver.GetLogs(func_str)) {
        WriteLog(log, out_file);
    }
    return 0;
}