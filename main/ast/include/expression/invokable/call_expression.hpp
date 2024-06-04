/**
 * @file call_expression.hpp
 * @brief Declaration of the call expression class.
 */

// Ensure this file is included only once
#pragma once

 // Include the expression interface
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a call expression in the abstract syntax tree (AST).
 *
 * This class inherits from the IExpression interface and represents a expression
 * that holds an call function in the AST.
 */
class FCallExpression final : public IExpression
{
    ExpressionPtr m_identifier;
    std::vector<ExpressionPtr> m_arguments;

public:

    FCallExpression(ExpressionPtr identifier, std::vector<ExpressionPtr> arguments);

    /**
     * @brief Evaluates the function call expression.
     * @param context The context in which to evaluate the expression.
     * @return The result of the function call.
     */
    Value Evaluate(const FContext& context) const override;
};
