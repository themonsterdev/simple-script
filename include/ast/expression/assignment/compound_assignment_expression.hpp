/**
 * @file compound_assignment_expression.hpp
 * @brief Declaration of the compound assignment expression class.
 */

 // Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FCompoundAssignmentExpression final : public IExpression
{
    std::string m_assignment;
    ExpressionPtr m_identifier;
    ExpressionPtr m_expression;

public:

    FCompoundAssignmentExpression(
        const std::string& assignment,
        ExpressionPtr identifier,
        ExpressionPtr expression
    );

    ValuePtr Evaluate(const FContext& context) const override;
};
