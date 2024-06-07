/**
 * @file while_loop_statement.cpp
 * @brief Implementation of the while loop statement class.
 */

// Include the header file for expressions
#include "statement/loop/while_loop_statement.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

#include "boolean_value.hpp"
#include "number_value.hpp"

FWhileLoopStatement::FWhileLoopStatement(ExpressionPtr condition, StatementPtr body)
    : m_condition(std::move(condition))
    , m_body(std::move(body))
{}

void FWhileLoopStatement::Execute(const FContext& context) const
{
    // Evaluate the condition of the while loop
    bool conditionResult = true; // Initialize to true to ensure the loop is executed at least once

    while (conditionResult)
    {
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
            // Handle an error if the condition does not evaluate to a boolean
            throw std::runtime_error("The condition must evaluate to a boolean value.");
        }

        // Execute the body of the while loop if the condition is true
        if (conditionResult)
        {
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
        }
    }
}
