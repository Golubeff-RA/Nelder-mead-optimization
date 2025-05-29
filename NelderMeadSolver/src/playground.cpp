#include <filesystem>
#include <fstream>
#include <iostream>
#include <tuple>

#include "solver.h"

using Params = std::tuple<size_t, double, double, double, double, double, double>;
using std::get;
using std::to_string;

Params ParseParams(const std::string& str) {
    std::istringstream iss(str);
    char sep;
    Params params;
    iss >> std::get<0>(params) >> std::get<1>(params) >> std::get<2>(params) >>
        std::get<3>(params) >> std::get<4>(params) >> sep >> std::get<5>(params) >> sep >>
        std::get<6>(params);
    return params;
};

int main(int argc, char* argv[]) {
    std::string filename;
    std::cin >> filename;
    std::ifstream input(filename);
    SLV::LoggerPtr logger{SLV::Logger::GetLogger()};

    while (!input.eof()) {
        std::string func, cnt_launchs;
        std::getline(input, func);
        std::cout << func;
        std::getline(input, cnt_launchs);
        std::cout << cnt_launchs;
        size_t cnt = std::stoul(cnt_launchs);
        for (size_t i = 0; i < cnt && !input.eof(); ++i) {
            std::string settings;
            std::getline(input, settings);
            Params params = ParseParams(settings);
            Point p{{get<5>(params), get<6>(params)}};
            SLV::NelderMeadSolver solver(logger, get<4>(params), get<2>(params), get<3>(params));
            solver.Optimize({func, get<0>(params), get<1>(params), p});
            std::string new_file = filename + "/" + func + "_" + to_string(get<0>(params)) + "_" +
                                   to_string(get<1>(params)) + "_" + to_string(get<2>(params)) +
                                   "_" + to_string(get<3>(params)) + "_" +
                                   to_string(get<4>(params)) + "_" + to_string(get<5>(params)) +
                                   "_" + to_string(get<6>(params)) + ".txt";
            std::ofstream out(new_file);
            auto logs = logger->GetLogs(&solver);
            for (const auto& log : logs) {
                out << log.func_val << " " << log.measure << std::endl;
            }
            out.close();
        }
    }
}