#include"ExpressionParse.h"
#include<map>

class PostStringTransfer
{
private:
    std::vector<std::string> _expression;
    std::vector<std::string> _postExpression;
    std::stack<std::string> _stack;
    std::map<std::string, int> _map = {
       { "(", 0 },
       { ")", 0 },
       { "+", 1 },
       { "-", 2 },
       { "*", 3 },
       { "/", 3 },
    };

    bool CheckOperandsMore(std::string operand1, std::string operand2) { return _map[operand1] >= _map[operand2]; }
    bool isOperand(std::string operand) { return (_map.count(operand) != 0 && operand != "(" && operand != ")"); }

    void openScobActions(std::string str)
    {
        _stack.push(str);
    }

    void closeScobActions(std::string str)
    {
        while (_stack.top() != "(")
        {
            _postExpression.push_back(_stack.top());
            _stack.pop();
        }
        _stack.pop();
    }

    void operandActions(std::string str)
    {
        while (!_stack.empty() && CheckOperandsMore(_stack.top(), str))
        {
            _postExpression.push_back(_stack.top());
            _stack.pop();
        }
        _stack.push(str);
    }

    void numberActions(std::string str)
    {
        _postExpression.push_back(str);
    }

    void FillPostfixstring()
    {
        for (auto str : _expression)
        {
            if (str == "(") openScobActions(str);
            else if (str == ")") closeScobActions(str);
            else if (isOperand(str)) operandActions(str);
            else numberActions(str);
        }

        while (!_stack.empty())
        {
            _postExpression.push_back(_stack.top());
            _stack.pop();
        }

    }

public:
    PostStringTransfer(std::string expression) {
        _expression = ExpressionParser(expression).GetPraseString();
    }

    std::vector<std::string> GetPostfixString()
    {
        //new DataValidator().Check(_expression);
        //new ScobkaValidater().Check(_expression);

        FillPostfixstring();

        //new OperandValidator().Check(_postExpression);

        return _postExpression;
    }
};