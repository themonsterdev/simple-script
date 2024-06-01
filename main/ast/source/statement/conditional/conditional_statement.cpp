/**
 * @file conditional_statement.cpp
 * @brief Implementation of the conditional statement class.
 */

// Include the declaration of the conditional statement class
#include "statement/conditional/conditional_statement.hpp"

// For runtime_error
#include <stdexcept>

FConditionalStatement::FConditionalStatement(ExpressionPtr condition, StatementPtr ifStatement)
    : m_condition(std::move(condition))
    , m_ifStatement(std::move(ifStatement))
{}

void FConditionalStatement::Execute(const FContext& context) const
{
    bool condition = EvaluateCondition(context);

    // If the condition is true, execute the associated statement
    if (condition)
    {
        m_ifStatement->Execute(context);
    }
    else
    {
        // If there are else-if statements, try to execute them
        if (!m_elseIfStatements.empty())
        {
            for (const auto& elseIfStatement : m_elseIfStatements)
            {
                const auto& conditionStatement = dynamic_cast<FConditionalStatement*>(elseIfStatement.get());

                // If the else-if condition is true, execute its associated statement
                if (conditionStatement && conditionStatement->EvaluateCondition(context))
                {
                    conditionStatement->Execute(context);
                    return; // Exit after executing the first true else-if statement
                }
            }
        }

        // If no condition is true and there is an else statement, execute it
        if (m_elseStatement)
        {
            m_elseStatement->Execute(context);
        }
    }
}

bool FConditionalStatement::EvaluateCondition(const FContext& context) const
{
    // Evaluate the condition expression
    Value conditionValue = m_condition->Evaluate(context);

    bool conditionResult = false;

    // Check if the condition value is an integer or a boolean
    if (std::holds_alternative<int>(conditionValue))
    {
        conditionResult = std::get<int>(conditionValue) > 0;
    }
    else if (std::holds_alternative<bool>(conditionValue))
    {
        conditionResult = std::get<bool>(conditionValue);
    }
    else // Throw an exception for invalid condition types
    {
        throw std::runtime_error("Invalid expression type for conditional statement");
    }

    return conditionResult;
}

void FConditionalStatement::AddElseIfStatement(StatementPtr elseIfStatement)
{
    // Add an else-if statement to the list
    m_elseIfStatements.push_back(std::move(elseIfStatement));
}

void FConditionalStatement::SetElseStatement(StatementPtr elseStatement)
{
    // Set the else statement
    m_elseStatement = std::move(elseStatement);
}

const ExpressionPtr& FConditionalStatement::GetCondition() const
{
    // Return a constant reference to the condition expression
    return m_condition;
}

const StatementPtr& FConditionalStatement::GetIfStatement() const
{
    // Return a constant reference to the if statement
    return m_ifStatement;
}

const StatementList& FConditionalStatement::GetElseIfStatements() const
{
    // Return a constant reference to the list of else-if statements
    return m_elseIfStatements;
}

const StatementPtr& FConditionalStatement::GetElseStatement() const
{
    // Return a constant reference to the else statement
    return m_elseStatement;
}
