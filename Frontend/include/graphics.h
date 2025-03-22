#include "point.h"
#include "solver.h"
//#include "Function.h"

class AppUI {
private:
    NelderMeadSolver _solver;
    char _printFunction[128] = "";
    char _inputFunction[128] = "";
    char* _defaultString;
    Point _testPoint;
    double _testAnswer = 0;
    std::list<Log> _logs = std::list<Log>();
    bool _printPoint = false;
    bool _printDefault = false;

    void printPoint(const Point& point);
    void readFunction();
    void clearFunction();

public:
    AppUI(char* defaultString, Point testPoint);
    AppUI();
    ~AppUI();

    void initFrame();
    void showIputWindow();
    void showOutputWindow();
};
