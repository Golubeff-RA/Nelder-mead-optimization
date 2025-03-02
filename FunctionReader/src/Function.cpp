#include"Function.h"



Function::Function(std::string expression, std::vector<double> vecPoint) :
	expression(expression),
	vecPoint(vecPoint) {
};

void Function::Decode() {
	for (size_t pos = 0; pos < expression.length(); pos++) {
		if (expression[pos] == 'x')
		{
			ChangeByPos(pos);
		}
	}
};

void Function::Print() {
	std::cout << expression;
}

void Function::DecodeIndex(size_t pos, std::string& ind)
{
	for (; pos < expression.length() && '0' <= expression[pos] && expression[pos] <= '9'; ++pos) {
		ind.push_back(expression[pos]);
	}

	if (ind.length() == 0) {
		throw std::runtime_error("incorrect expression");
	}
}

std::string Function::ConvertToString(const double& x, const int precision)
{
	static std::ostringstream ss;
	ss.str("");
	ss << std::fixed << std::setprecision(precision) << x;

	return ss.str();
}

void Function::ChangeByPos(size_t pos) {
	std::string ind = "";
	DecodeIndex(pos + 1, ind);

	std::string string_value = ConvertToString(vecPoint[std::stoi(ind) - 1], std::max((int)ind.length(), 4));

	int size_dif = (int)string_value.length() - (int)ind.length() - 1;
	try {
		expression.resize(expression.length() + size_dif);
	}
	catch (const std::exception&)
	{
		std::cout << "Something wrong" << std::endl;
	}

	for (size_t i = expression.length() - 1; i + 1 >= pos + 1; --i) {
		if (i >= pos + (int)string_value.length()) {
			expression[i] = expression[i - size_dif];
		}
		else {
			expression[i] = string_value[i - pos];
		}
	}
}

double Function::Calculate() {
	return PostStringCalculater(expression).Calculate();
}