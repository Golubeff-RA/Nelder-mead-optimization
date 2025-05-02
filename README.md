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
# UML-диаграмма 
@startuml
class Point {
  - data_: std::vector<double>
  + Point(dimensions: size_t)
  + Point(data: const std::vector<double>&)
  + Point(data: std::initializer_list<double>&&)
  + Point(other: const Point&)
  + Point(other: Point&&)
  + operator=(other: const Point&): Point&
  + operator=(other: Point&&): Point&
  + ~Point()
  + Size(): size_t
  + operator[](idx: size_t) const: double
  + operator[](idx: size_t): double&
  + operator+=(other: const Point&): Point&
  + operator-=(other: const Point&): Point&
  + operator*=(coef: double): Point&
  + operator+(left: const Point&, right: const Point&): Point
  + operator-(left: const Point&, right: const Point&): Point
  + operator*(point: const Point&, coef: double): Point
  + operator*(coef: double, point: const Point&): Point
}

class Log {
  + points: std::vector<Point>
  + measure: double
  + func_val: double
}

class Function {
    - expression_: std::string
    - vecOperand_: std::vector<std::string>
    + Function(expression: std::string)
    + Calculate(point: Point&): double
}

class NelderMeadSolver {
  - eps_: double
  - epoch_: size_t
  - optimized_functions_: std::map<std::string, std::list<Log>>
  - expan_coef_: const double
  - shrnk_coef_: const double
  - refle_coef_: const double
  - update_simplex_: const size_t
  + NelderMeadSolver(eps: double = 10e-5, epoch: size_t = 100)
  + Optimize(function: const std::string&, start_point: const Point&): double
  + CountDim(function: const std::string&): size_t
  + GetLogs(function: const std::string&): std::list<Log>
  + eps() const: double
  + eps(): double&
  + epoch() const: size_t
  + epoch(): size_t&
  - CalcCenter_(simplex: const std::multimap<double, Point>&): Point
  - GenerateSimplex_(dim: size_t, start_point: Point, func: Function&): std::multimap<double, Point>
  - SimplexToVector_(simplex: const std::multimap<double, Point>&): std::vector<Point>
  - LocalShrink_(func: Function&, simplex: std::multimap<double, Point>&, center: const Point&): void
  - GlobalShrink_(func: Function&, simplex: std::multimap<double, Point>&): void
}

class AppUI {
  -_solver: NelderMeadSolver
  -_readedFunction: char[128]
  -_inputFunction: char[128]
  -_defaultString: char*
  -_startPoint: Point
  -_logs: std::list<Log>
  -_printFunction: bool
  -_optimizeFunction: bool
  -_printDefault: bool
  -_showSettings: bool
  -_showLogs: bool
  -_answer: double
  -_error: float
  -_iterations: int
  -_dimensions: size_t

  +AppUI(defaultString: char*)
  +AppUI()
  +~AppUI()
  +initFrame():void
  +showIputWindow():void
  +showOutputWindow():void
  +showSettingsWindow():void
  +isExpressionCorrect(expression: std::string): bool
  -printPoint(point: const Point&): void
  -readFunction(): void
  -optimizeFunction(): void
  -clearFunction(): void
}

NelderMeadSolver "1" -- "0..*" Log : contains
NelderMeadSolver "1" -- "1" Function : uses
NelderMeadSolver "1" -- "1..*" Point : uses
Function "1" -- "1" Point : uses
AppUI "1" -- "1" NelderMeadSolver: uses
AppUI "1" -- "1" Point: uses
AppUI "1" -- "0..*" Log: uses

note right of Log::points
    Vector of points in simplex
end note

note right of Point::data_
    Stores the coordinates of the point
end note
note right of NelderMeadSolver::optimized_functions_
    Store logs for each function that has been optimized
end note

note right of NelderMeadSolver
    Class for finding the minimum of a function using the Nelder-Mead method.
end note

note right of AppUI
    Class for UI interaction, optimization, and logs handling
end note

note right of Function
    Class for expression calculation
end note
@enduml
