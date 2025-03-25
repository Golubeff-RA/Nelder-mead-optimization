#include "graphics.h"

AppUI::AppUI(char* defaultString, Point testPoint)
: _defaultString{defaultString}, _testPoint{testPoint} {
}

AppUI::AppUI() : _testPoint{Point{std::vector<double>{1, 2, 3, 4}}} {
    _defaultString = new char[strlen(stringRes::read_function_string) + 1];
    strcpy(_defaultString, stringRes::read_function_string);
}