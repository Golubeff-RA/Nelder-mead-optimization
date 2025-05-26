#include "post_string_transfer.h"

namespace FR {
    PostStringTransfer::PostStringTransfer(std::string expression) {
        expression_ = expression_parser(expression).GetPraseExpression();
    }
    void PostStringTransfer::OpenScobActions(std::string str) {
        stack_.push(str);
    }

    void PostStringTransfer::CloseScobActions(std::string str) {
        while (stack_.top() != "(") {
            postExpression_.push_back(stack_.top());
            stack_.pop();
        }
        stack_.pop();
    }

    void PostStringTransfer::OperandActions(std::string str) {
        while (!stack_.empty() && CheckOperandsMore(stack_.top(), str)) {
            postExpression_.push_back(stack_.top());
            stack_.pop();
        }
        stack_.push(str);
    }

    void PostStringTransfer::NumberActions(std::string str) {
        postExpression_.push_back(str);
    }

    void PostStringTransfer::FillPostfixstring() {
        for (auto str : expression_) {
            if (str == "(")
                OpenScobActions(str);
            else if (str == ")")
                CloseScobActions(str);
            else if (IsOperation(str))
                OperandActions(str);
            else
                NumberActions(str);
        }

        while (!stack_.empty()) {
            postExpression_.push_back(stack_.top());
            stack_.pop();
        }
    }

    std::vector<std::string> PostStringTransfer::GetPostfixString() {
        FillPostfixstring();
        return postExpression_;
    }
} // end FR