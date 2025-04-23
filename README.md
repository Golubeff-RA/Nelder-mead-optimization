# Nelder-Mead-optimization
Приложение под Linux, оптимизирующее функцию, заданную аналитически, с помощью эвристического алгоритма Нелдера-Мида
# Команда
Голубев Р. - поиск библиотек, CMake (ломаем, потом 3 дня чиним), алгоритм оптимизации.
<br>Пудков М. - frontend, предобработка входящей функции, тестирование.
<br>Самохин В. - алгоритм вычисления функции в точке, критика вычислительной сложности, исправление багов за всеми остальными.

# UI
Frontend(UI) нашего приложения написан с помощью открытой библиотеки  [ImGUI](https://github.com/ocornut/imgui). Она достаточно простая и легковесная, по сравнению с Qt Framework. Пока что приложение однопоточное, т. к. оптимизатор работает сравнительно быстро и мы не хотим париться с синхронизацией потоков.

# Алгоритм оптимизации
Для начала оптимизации выбирается стартовая точка, вокруг неё строится симплекс из линейно независимых векторов. Пример старт = (0, 0, 0), симплекс (1, 0, 0), (0, -1, 0), (0, 0, 1) + стартовая (0, 0, 0). Т. е. к координатам стартовой точки прибавляем 1 или -1 (случайно) в каждом измерении. Остановка оптимизации по числу шагов или Евклидовой мере симлекса (объёму). <br> Hint: Каждые 25 шагов (параметр "update_simlex_" в Solver) перестраиваем симлекс, чтобы избежать залипания в очень многомерных функциях.
# Основные классы
Point - обёртка над std::vector для удобной работы с n-мерными точками
``` c++
class Point {
public:
    Point(size_t dimensions);
    Point(const std::vector<double>& data);
    Point(std::initializer_list<double>&& data);
    // rule of 5 realisation //
    Point(const Point& other);
    Point(Point&& other);
    Point& operator=(const Point& other);

    Point& operator=(Point&& other);
    ~Point();
    // ... //

    size_t Size() const;
    double operator[](size_t idx) const;

    double& operator[](size_t idx);

    Point& operator+=(const Point& other);

    Point& operator-=(const Point& other);

    Point& operator*=(double coef);

    friend Point operator+(const Point& left, const Point& right);

    friend Point operator-(const Point& left, const Point& right);

    friend Point operator*(const Point& point, double coef);

    friend Point operator*(double coef, const Point& point);


private:
    std::vector<double> data_;
};
```
Function - переводит исходную строку функции в польскую запись при создании и считает значение в точке с помощью метода Calculate.
```c++
class Function {
private:
    std::string expression_;
    std::vector<std::string> vecOperand_;

public:
    Function(std::string expression);
    double Calculate(Point& point);
}; 
```
Solver - оптимизатор, в котором и реализован сам алгоритм Нелдера-Мида.
``` c++
struct Log {
    std::vector<Point> points;  // точки симплекса
    double measure;             // мера симплекса
    double func_val;            // значение функции
};

class NelderMeadSolver {
public:
    NelderMeadSolver(double eps = 10e-5, size_t epoch = 100);

    // вернёт найденный минимум функции стартуя с заданной точки
    double Optimize(const std::string& function, const Point& start_point);

    // счтает переменных в оптимизируемой функции
    size_t CountDim(const std::string& function);

    // вернёт логи процесса оптимизации функции
    std::list<Log> GetLogs(const std::string& function);

    double eps() const;

    double& eps();

    size_t epoch() const;

    size_t& epoch();

private:
    double eps_;
    size_t epoch_;
    std::map<std::string, std::list<Log>> optimized_functions_;
    const double expan_coef_ = 2;
    const double shrnk_coef_ = 0.5;
    const double refle_coef_ = 1;
    const size_t update_simplex_ = 25;

    // вычисляет центр "лучших" точек симплекса
    Point CalcCenter_(const std::multimap<double, Point>& simplex);

    // генерирует опорный симплекс
    std::multimap<double, Point> GenerateSimplex_(size_t dim, Point start_point, Function& func);

    // преобразует симплекс в вектор точек
    std::vector<Point> SimplexToVector_(const std::multimap<double, Point>& simplex);

    // оператор локального сжатия
    void LocalShrink_(Function& func, std::multimap<double, Point>& simplex, const Point& center);

    // оператор глобального сжатия всего симплекса
    void GlobalShrink_(Function& func, std::multimap<double, Point>& simplex);
};
```
