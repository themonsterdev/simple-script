/**
 * @file do_while_loop_statement.hpp
 * @brief Declaration of the do-while loop statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

/**
 * @brief Represents a do-while loop statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * iteratively executes a body of code at least once and then continues to execute
 * the body as long as a specified condition evaluates to true.
 */
class FDoWhileLoopStatement final : public IStatement
{
    // The body of the do-while loop.
    StatementPtr m_body;

    // The condition of the do-while loop.
    ExpressionPtr m_condition;

public:

    /**
     * @brief Constructs an FDoWhileLoopStatement with the given body and condition.
     * @param body The body of the loop to be executed.
     * @param condition The condition expression that determines whether to continue the loop.
     */
    FDoWhileLoopStatement(StatementPtr body, ExpressionPtr condition);

    /**
     * @brief Executes this do-while loop within the given context.
     *
     * This method executes the body of the loop at least once and then repeatedly
     * executes the body as long as the condition evaluates to true.
     * @param context The context in which to execute the loop.
     */
    virtual void Execute(const FContext& context) const override;
};
