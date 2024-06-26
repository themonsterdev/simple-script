#pragma once

#include "ast/expression/interface/expression.hpp"
#include "value/object_value.hpp"

class FAccessExpression final : public IExpression
{
    ExpressionPtr m_expression;
    std::string m_op; // '.' or '->'
    std::string m_memberName;

public:

    FAccessExpression(
        ExpressionPtr expression,
        std::string op,
        std::string memberName
    );

    ValuePtr Evaluate(const FContext& context) const override;
};
