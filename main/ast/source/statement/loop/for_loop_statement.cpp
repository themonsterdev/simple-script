/**
 * @file for_loop_statement.cpp
 * @brief Implementation of the for loop statement class.
 */

// Include the header file for expressions
#include "statement/loop/for_loop_statement.hpp"
#include <stdexcept>

FForLoopStatement::FForLoopStatement(StatementPtr initialization, ExpressionPtr condition, StatementPtr update, StatementPtr body)
    : m_initialization(std::move(initialization))
    , m_condition(std::move(condition))
    , m_update(std::move(update))
    , m_body(std::move(body))
{}

void FForLoopStatement::Execute(const FContext& context) const
{
    // Evaluate the initialization statement (e.g., var i = 0;)
    m_initialization->Execute(context);

    // Evaluate the condition expression (e.g., i < 0;) before each iteration
    bool conditionResult = false; // Initialize to false to ensure loop is executed at least once

    while (conditionResult)
    {
        // Execute the body of the loop
        m_body->Execute(context);

        // Evaluate the condition expression at the end of each iteration
        Value conditionValue = m_condition->Evaluate(context);

        if (std::holds_alternative<bool>(conditionValue))
        {
            conditionResult = std::get<bool>(conditionValue);
        }
        else
        {
            // Handle error if the condition does not evaluate to a boolean
            throw std::runtime_error("Condition must evaluate to a boolean value.");
        }

        // Execute the update statement (e.g., i++) after each iteration
        m_update->Execute(context);
    }
}
