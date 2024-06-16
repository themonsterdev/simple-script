/**
 * @file postfix_expression.hpp
 * @brief Declaration of the postfix expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"
#include <string>

class FPostfixExpression final : public IExpression
{
    ExpressionPtr m_expression;
    std::string m_op; // '++' or '--'

public:

    FPostfixExpression(ExpressionPtr expression, std::string op);
    ValuePtr Evaluate(const FContext& context) const override;
};
