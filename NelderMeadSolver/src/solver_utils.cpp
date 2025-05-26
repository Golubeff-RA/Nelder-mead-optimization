#include <set>
#include "solver.h"

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
            if(num.size() > 0) {
                vars.insert(std::stoull(num));
            } else {
                throw std::runtime_error("invalid variable name");
            }
        }
        ++idx;
    }

    //not have vars in expression
    if (vars.size() == 0) {
        return 0; 
    }
    if (*(std::prev(vars.end())) != vars.size()) {
        throw std::runtime_error("Wrong variable numerization!");
    }
    return *(std::prev(vars.end()));
}

Point NelderMeadSolver::CalcCenter_(const std::multimap<double, Point>& simplex) {
    Point center(simplex.size() - 1);
    for (auto it = simplex.begin(); it != std::prev(simplex.end()); ++it) {
        center += it->second;
    }

    return center *= 1.0 / (simplex.size() - 1);
}

std::multimap<double, Point> NelderMeadSolver::GenerateSimplex_(size_t dim, Point start_point,
                                                                FR::Function& func) {
    std::multimap<double, Point> simplex;
    simplex.insert({func.Calculate(start_point), start_point});

    for (size_t idx = 1; idx <= dim; ++idx) {
        Point point(start_point);
        point[idx - 1] = point[idx - 1] + (rand() % 2 == 0 ? -1 : 1) * 1.0;
        simplex.insert({func.Calculate(point), point});
    }

    return simplex;
}

std::vector<Point> NelderMeadSolver::SimplexToVector_(const std::multimap<double, Point>& simplex) {
    std::vector<Point> points;
    points.reserve(simplex.size());
    for (auto p : simplex) {
        points.push_back(p.second);
    }

    return points;
}

void NelderMeadSolver::LocalShrink_(FR::Function& func, std::multimap<double, Point>& simplex,
                                    const Point& center) {
    Point worst{std::prev(simplex.end())->second};
    double f_h = std::prev(simplex.end())->first;
    Point shrinked = shrnk_coef_ * worst + (1 - shrnk_coef_) * center;
    double f_s = func.Calculate(shrinked);
    if (f_s < f_h) {
        simplex.erase(std::prev(simplex.end()));
        simplex.insert({f_s, shrinked});
    } else {
        GlobalShrink_(func, simplex);
    }
}

void NelderMeadSolver::GlobalShrink_(FR::Function& func, std::multimap<double, Point>& simplex) {
    Point best{simplex.begin()->second};
    std::vector<Point> shrinked;
    shrinked.reserve(simplex.size());
    //std::cout << "Global shrink";
    for (auto it = simplex.begin(); it != simplex.end(); ++it) {
        shrinked.push_back(best + 0.5 * (it->second - best));
    }

    simplex.clear();
    for (Point& p : shrinked) {
        simplex.insert({func.Calculate(p), p});
    }
}