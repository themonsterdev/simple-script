/**
 * @file do_while_loop_statement.cpp
 * @brief Implementation of the do-while loop statement class.
 */

// Include the header file for expressions
#include "statement/loop/do_while_loop_statement.hpp"
#include <stdexcept>

FDoWhileLoopStatement::FDoWhileLoopStatement(StatementPtr body, ExpressionPtr condition)
    : m_condition(std::move(condition))
    , m_body(std::move(body))
{}

void FDoWhileLoopStatement::Execute(const FContext& context) const
{
    // Evaluate the condition expression before entering the loop
    bool conditionResult = true; // Initialize to true to ensure loop is executed at least once

    do
    {
        // Execute the body of the loop
        m_body->Execute(context);

        // Evaluate the condition of the loop
        Value conditionValue = m_condition->Evaluate(context);

        if (std::holds_alternative<bool>(conditionValue))
        {
            conditionResult = std::get<bool>(conditionValue);
        }
        else if (std::holds_alternative<int>(conditionValue))
        {
            conditionResult = std::get<int>(conditionValue) > 0;
        }
        else
        {
            // Handle error if the condition does not evaluate to a boolean
            throw std::runtime_error("Condition must evaluate to a boolean value.");
        }
    } while (conditionResult);
}
