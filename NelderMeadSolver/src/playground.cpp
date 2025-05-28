#include <iostream>

#include "solver.h"

int main(int argc, char* argv[]) {
    SLV::LoggerPtr logger = SLV::Logger::GetLogger();
    SLV::NelderMeadSolver solver(logger);
    SLV::OptInfo params;
    std::cout << "Введите функцию: ";
    std::getline(std::cin, params.function);
    size_t cnt_dim = 0;
    try {
        cnt_dim = solver.CountDim(params.function);
    } catch (std::runtime_error& ex) {
        std::cerr << "Произошла ошибка: " << ex.what();
        return 1;
    }

    std::cout << "Введите стартовую точку. Размерность: " << cnt_dim << std::endl;
    std::vector<double> coords(cnt_dim, 0);
    for (size_t i = 0; i < cnt_dim; ++i) {
        std::cout << "#1 - ";
        std::cin >> coords[i];
    }
    params.start_point = Point(coords);

    std::cout << "Введите число итераций: ";
    std::cin >> params.epoch;

    std::cout << "Введите мин меру симплекса: ";
    std::cin >> params.measure;

    std::cout << "min Q(X) = " << solver.Optimize(params);
    logger->WriteHTML(&solver);
    return 0;
}