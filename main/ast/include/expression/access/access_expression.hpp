#pragma once

#include "expression/interface/expression.hpp"

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

    ValuePtr EvaluateDotOperator(const ObjectValuePtr& object, const FContext& context) const;
    ValuePtr CallObjectMethod(const ObjectValuePtr& object, const FContext& context) const;
};
