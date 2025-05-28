#include "solver.h"

#include <set>

NelderMeadSolver::NelderMeadSolver(LoggerPtr log_ptr, double expan_coef, double shrnk_coef,
                                   double refle_coef, size_t update_simplex)
    : log_ptr_(log_ptr),
      expan_coef_(expan_coef),
      shrnk_coef_(shrnk_coef),
      refle_coef_(refle_coef),
      update_simplex_(update_simplex) {
}

double NelderMeadSolver::Optimize(const OptInfo& info) {
    srand(time(0));
    double measure = 100;
    LogList current_optimization;
    size_t dim_size = NelderMeadSolver::CountDim(info.function);
    FR::Function func{info.function};
    Simplex simplex{GenerateSimplex_(dim_size, info.start_point, func)};
    for (size_t i = 0; i < std::max((size_t)1ul, info.epoch / update_simplex_); ++i) {
        size_t counter = 0;
        while (counter < std::min(update_simplex_, info.epoch) && measure > info.measure) {
            ++counter;
            measure = Measure(simplex);
            current_optimization.push_back({simplex.begin()->first, measure, simplex.begin()->second});
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

    log_ptr_->WriteHTML(info, current_optimization, this);
    return simplex.begin()->first;
}

size_t NelderMeadSolver::CountDim(const std::string& function) {
    std::set<size_t> vars;
    size_t idx = 0;
    while (idx < function.size()) {
        if (function[idx] == 'x') {
            ++idx;
            std::string num{};
            while (idx < function.size() && function[idx] >= '0' && function[idx] <= '9') {
                num.push_back(function[idx]);
                ++idx;
            }
            if (num.size() > 0) {
                vars.insert(std::stoull(num));
            } else {
                throw std::runtime_error("invalid variable name");
            }
        }
        ++idx;
    }

    // not have vars in expression
    if (vars.size() == 0) {
        return 0;
    }
    if (*(std::prev(vars.end())) != vars.size()) {
        throw std::runtime_error("Wrong variable numerization!");
    }
    return *(std::prev(vars.end()));
}

std::string NelderMeadSolver::GetHyperparams() const {
    std::ostringstream oss;
    oss << "Reflect: " << refle_coef_ << " Shrink: " << shrnk_coef_ << " Expan: " << expan_coef_ << " Upd simplex: " << update_simplex_;
    return oss.str();
}