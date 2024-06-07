/**
 * @file do_while_loop_statement.cpp
 * @brief Implementation of the do-while loop statement class.
 */

// Include the header file for expressions
#include "statement/loop/do_while_loop_statement.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

#include "boolean_value.hpp"
#include "number_value.hpp"

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

        if (context.HasReturnValue())
        {
            // Exit the loop if a return statement was executed
            break;
        }

        // Check if a continue statement has been encountered
        if (context.GetContinueFlag())
        {
            // Reset the continue flag for the next iteration
            context.SetContinueFlag(false);
            continue; // Move to the next iteration
        }

        // Evaluate the condition of the loop
        ValuePtr conditionValue = m_condition->Evaluate(context);

        if (conditionValue->IsBoolean())
        {
            const auto& result = std::dynamic_pointer_cast<FBooleanValue>(conditionValue);

            conditionResult = result->GetValue();
        }
        else if (conditionValue->IsNumber())
        {
            const auto& result = std::dynamic_pointer_cast<FNumberValue>(conditionValue);

            conditionResult = result->GetValue() > 0;
        }
        else
        {
            // Handle error if the condition does not evaluate to a boolean
            throw std::runtime_error("Condition must evaluate to a boolean value.");
        }
    } while (conditionResult);
}
