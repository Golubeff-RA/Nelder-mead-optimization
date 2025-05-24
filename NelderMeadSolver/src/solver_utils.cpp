#include "solver.h"

Point NelderMeadSolver::CalcCenter_(const Simplex& simplex) {
    Point center(simplex.size() - 1);
    for (auto it = simplex.begin(); it != std::prev(simplex.end()); ++it) {
        center += it->second;
    }

    return center *= 1.0 / (simplex.size() - 1);
}

Simplex NelderMeadSolver::GenerateSimplex_(size_t dim, Point start_point, Function& func) {
    Simplex simplex;
    simplex.insert({func.Calculate(start_point), start_point});

    for (size_t idx = 1; idx <= dim; ++idx) {
        Point point(start_point);
        point[idx - 1] = point[idx - 1] + (rand() % 2 == 0 ? -1 : 1) * 1.0;
        simplex.insert({func.Calculate(point), point});
    }

    return simplex;
}

std::vector<Point> NelderMeadSolver::SimplexToVector_(const Simplex& simplex) {
    std::vector<Point> points;
    points.reserve(simplex.size());
    for (auto p : simplex) {
        points.push_back(p.second);
    }

    return points;
}

void NelderMeadSolver::LocalShrink_(Function& func, Simplex& simplex, const Point& center) {
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

void NelderMeadSolver::GlobalShrink_(Function& func, Simplex& simplex) {
    Point best{simplex.begin()->second};
    std::vector<Point> shrinked;
    shrinked.reserve(simplex.size());
    // std::cout << "Global shrink";
    for (auto it = simplex.begin(); it != simplex.end(); ++it) {
        shrinked.push_back(best + 0.5 * (it->second - best));
    }

    simplex.clear();
    for (Point& p : shrinked) {
        simplex.insert({func.Calculate(p), p});
    }
}