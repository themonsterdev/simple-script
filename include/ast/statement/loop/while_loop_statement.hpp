/**
 * @file while_loop_statement.hpp
 * @brief Declaration of the while loop statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

// Include the interface for expressions
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a while loop statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * repeatedly executes a body of code while a specified condition is true.
 */
class FWhileLoopStatement final : public IStatement
{
    // The condition of the while loop.
    ExpressionPtr m_condition;

    // The body of the while loop.
    StatementPtr m_body;

public:

    /**
     * @brief Constructs an FWhileLoopStatement with the given condition and body.
     * @param condition The condition that determines whether the loop should continue.
     * @param body The body of the loop to be executed repeatedly.
     */
    FWhileLoopStatement(ExpressionPtr condition, StatementPtr body);

    /**
     * @brief Executes this while loop within the given context.
     *
     * This method evaluates the condition and repeatedly executes the loop body
     * as long as the condition evaluates to true.
     * @param context The context in which to execute the loop.
     */
    void Execute(const FContext& context) const override;
};
