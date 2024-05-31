/**
 * @file conditional_statement.cpp
 * @brief Implementation of the conditional statement class.
 */

 // Include the declaration of the conditional statement class
#include "statement/conditional_statement.hpp"

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
        // first condition
        m_ifStatement->Execute(context);
    }
    else
    {
        bool executed = false;

        if (m_elseIfStatements.size() > 0)
        {
            for (const auto& statement : m_elseIfStatements)
            {
                const auto& conditionStatement = dynamic_cast<FConditionalStatement*>(statement.get());

                if (conditionStatement && conditionStatement->EvaluateCondition(context))
                {
                    conditionStatement->Execute(context);
                    executed = true;
                    break;
                }
            }
        }

        if (!executed && m_elseStatement)
        {
            m_elseStatement->Execute(context);
        }
    }
}

bool FConditionalStatement::EvaluateCondition(const FContext& context) const
{
    // Evaluate conditional expression
    Value conditionValue = m_condition->Evaluate(context);

    bool conditionResult = false;

    // Check if both operands are integer/boolean
    if (std::holds_alternative<int>(conditionValue))
    {
        // Extract boolean value from the variants
        conditionResult = std::get<int>(conditionValue) > 0;
    }
    else if (std::holds_alternative<bool>(conditionValue))
    {
        // Extract boolean value from the variants
        conditionResult = std::get<bool>(conditionValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid expression type for conditional statement");
    }

    return conditionResult;
}

void FConditionalStatement::AddElseIfStatement(StatementPtr elseIfStatement)
{
    m_elseIfStatements.push_back(std::move(elseIfStatement));
}

void FConditionalStatement::SetElseStatement(StatementPtr elseStatement)
{
    m_elseStatement = std::move(elseStatement);
}

const ExpressionPtr& FConditionalStatement::GetCondition() const
{
    return m_condition;
}

const StatementPtr& FConditionalStatement::GetIfStatement() const
{
    return m_ifStatement;
}

const StatementList& FConditionalStatement::GetElseIfStatements() const
{
    return m_elseIfStatements;
}

const StatementPtr& FConditionalStatement::GetElseStatement() const
{
    return m_elseStatement;
}
