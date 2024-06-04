/**
 * @file switch_statement.cpp
 * @brief Implementation of the switch statement class.
 */

// Include the header file for the switch statement class
#include "statement/switch/switch_statement.hpp"

// Include declarations for context objects
#include "context.hpp"

// Constructor definition
FSwitchStatement::FSwitchStatement(ExpressionPtr condition, CaseStatementVector cases, DefaultStatementPtr defaultCase)
    // Initialize m_condition with the given condition
    : m_condition(std::move(condition))
    // Initialize m_cases with the given cases
    , m_cases(std::move(cases))
    // Initialize m_defaultCase with the given defaultCase
    , m_defaultCase(std::move(defaultCase))
{}

// Execute method definition
void FSwitchStatement::Execute(const FContext& context) const
{
    // Retrieve the value of the switch condition
    Value switchValue = m_condition->Evaluate(context);

    // Determine which case to execute based on the value of the condition
    bool caseExecuted = false;
    for (const auto& caseStatement : m_cases)
    {
        Value caseValue = caseStatement->GetCondition()->Evaluate(context);
        if (switchValue == caseValue)
        {
            // Execute the body of the corresponding case
            caseStatement->GetBody()->Execute(context);
            caseExecuted = true;
            break; // Exit the loop once the matching case is executed
        }
    }

    // If no matching case is found and there's a default case, execute it
    if (!caseExecuted && m_defaultCase != nullptr)
    {
        m_defaultCase->GetBody()->Execute(context);
    }
}

// GetCondition method definition
const ExpressionPtr& FSwitchStatement::GetCondition() const
{
    // Return a constant reference to the expression to be evaluated for the switch condition
    return m_condition;
}

// GetCases method definition
const CaseStatementVector& FSwitchStatement::GetCases() const
{
    // Return a constant reference to the list of case statements associated with this switch statement
    return m_cases;
}

// GetDefaultCase method definition
const DefaultStatementPtr& FSwitchStatement::GetDefaultCase() const
{
    // Return a constant reference to the default case statement associated with this switch statement
    return m_defaultCase;
}
