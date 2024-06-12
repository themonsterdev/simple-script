/**
 * @file expression_statement.hpp
 * @brief Declaration of the expression statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for language expressions
#include "ast/expression/interface/expression.hpp"

class FExpressionStatement : public IStatement
{
    ExpressionPtr m_expression;

public:

    FExpressionStatement(ExpressionPtr expression);

    void Execute(const FContext& context) const override;

    const ExpressionPtr& GetExpression() const;
};
