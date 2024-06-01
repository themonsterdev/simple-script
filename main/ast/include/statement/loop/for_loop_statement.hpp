/**
 * @file for_loop_statement.hpp
 * @brief Declaration of the for loop statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a for loop statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * iteratively executes a body of code based on initialization, condition, and update expressions.
 */
class FForLoopStatement final : public IStatement
{
    // The initialization expression of the for loop.
    StatementPtr m_initialization;

    // The condition expression of the for loop.
    ExpressionPtr m_condition;

    // The update expression of the for loop.
    StatementPtr m_update;

    // The body of the for loop.
    StatementPtr m_body;

public:

    /**
     * @brief Constructs an FForLoopStatement with the given initialization, condition, update, and body.
     * @param initialization The initialization expression of the for loop.
     * @param condition The condition expression that determines whether to continue the loop.
     * @param update The update expression executed after each iteration of the loop.
     * @param body The body of the loop to be executed iteratively.
     */
    FForLoopStatement(StatementPtr initialization, ExpressionPtr condition, StatementPtr update, StatementPtr body);

    /**
     * @brief Executes this for loop within the given context.
     *
     * This method evaluates the initialization expression, evaluates the condition expression
     * on each iteration, executes the loop body if the condition is true, and then executes
     * the update expression before the next iteration.
     * @param context The context in which to execute the loop.
     */
    virtual void Execute(const FContext& context) const override;
};
