#pragma once

#include "ast/expression/interface/expression.hpp"
#include "value/interface/value.hpp"

class FAccessMethodExpression final : public IExpression
{
    ExpressionPtr m_expression;
    std::string m_op; // '.' or '->'
    std::string m_memberName;
    ExpressionList m_arguments;

public:

    FAccessMethodExpression(
        ExpressionPtr expression,
        std::string op,
        std::string memberName
    );

    ValuePtr Evaluate(const FContext& context) const override;

    void SetArguments(ExpressionList arguments);
};

using AccessMethodExpressionPtr = std::unique_ptr<FAccessMethodExpression>;
