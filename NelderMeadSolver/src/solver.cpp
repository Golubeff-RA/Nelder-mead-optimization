#include "solver.h"

NelderMeadSolver::NelderMeadSolver(double eps, size_t epoch) : eps_(eps), epoch_(epoch) {
}

double NelderMeadSolver::Optimize(const std::string& function, const Point& start_point) {
    srand(time(0));
    std::list<Log> current_optimization;
    double measure = 100;
    size_t dim_size = CountDim(function);
    Function func{function};
    auto simplex{GenerateSimplex_(dim_size, start_point, func)};
    for (size_t i = 0; i < std::max(1ul, epoch_ / update_simplex_); ++i) {
        size_t counter = 0;
        while (counter < update_simplex_ && measure > eps_) {
            ++counter;
            auto vec_simplex = SimplexToVector_(simplex);
            measure = Measure(vec_simplex);
            current_optimization.push_back(Log{vec_simplex, measure, simplex.begin()->first});

            Point worst{std::prev(simplex.end())->second};
            Point center{CalcCenter_(simplex)};
            Point reflected = (1.0 + refle_coef_) * center - refle_coef_ * worst;
            // значение функции в отраженной точке
            double f_r = func.Calculate(reflected); 
            // лучшее значение функции
            double f_l = simplex.begin()->first;  
            // второе по лучшести
            double f_g = std::next(simplex.begin())->first;  
            // самое плохое значение функции
            double f_h = std::prev(simplex.end())->first;  

            // Q(X) в отраженной точке лучше лучшего значения
            if (f_r < f_l) {
                Point expanded = (1.0 - expan_coef_) * center + expan_coef_ * reflected;
                double f_e = func.Calculate(expanded);
                if (f_e < f_r) {
                    simplex.insert({f_e, expanded});
                } else {
                    simplex.insert({f_r, reflected});
                }
                simplex.erase(std::prev(simplex.end()));
                continue;
            }

            // Q(X) в отраженной точке между 2-мя лучшими значениями
            if (f_l <= f_r && f_r < f_g) {
                simplex.insert({f_r, reflected});
                simplex.erase(std::prev(simplex.end()));
                continue;
            }

            if (f_g <= f_r && f_r < f_h) {
                simplex.insert({f_r, reflected});
                simplex.erase(std::prev(simplex.end()));
                LocalShrink_(func, simplex, center);
                continue;
            }

            if (f_h <= f_r) {
                LocalShrink_(func, simplex, center);
                continue;
            }
        }
        simplex = GenerateSimplex_(dim_size, simplex.begin()->second, func);
    }

    optimized_functions_.erase(function);
    optimized_functions_.insert({function, std::move(current_optimization)});
    return simplex.begin()->first;
}

std::list<Log> NelderMeadSolver::GetLogs(const std::string& function) {
    return optimized_functions_.at(function);
}

double NelderMeadSolver::eps() const {
    return eps_;
}

double& NelderMeadSolver::eps() {
    return eps_;
}

size_t NelderMeadSolver::epoch() const {
    return epoch_;
}

size_t& NelderMeadSolver::epoch() {
    return epoch_;
}
