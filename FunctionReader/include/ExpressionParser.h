#include<iostream>
#include<stack>

class ExpressionParser{
        private:
        std::string _expression;
        std::stack<std::string> list_expression;

        std::string AddInList(std::string str, char symbol)
        {
            if (str != "")
            {
                list_expression.push(str);
            }
            if (symbol != ' ') list_expression.push("" + symbol);
            str = "";
            return str;          
        }

        void Parse()
        {
            std::string str = "";
            for (auto symbol : _expression)
            {
                if (symbol == ' ' || symbol == '(' || symbol == ')')
                {
                    str = AddInList(str, symbol);
                }
                else str += symbol;
            }
            str = AddInList(str, ' ');
        }

        public:
        ExpressionParser(std::string expression) : _expression(expression){};
        
        std::stack<std::string> GetPraseString()
        {
            Parse();
            return list_expression;
        }
};