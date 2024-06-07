/**
 * @file return_statement.cpp
 * @brief Implementation of the return statement class.
 */

#include "statement/control_flow/return_statement.hpp"
#include "context.hpp"
#include <stdexcept>

FReturnStatement::FReturnStatement(ExpressionPtr returnValue)
    : m_returnValue(std::move(returnValue))
{
    if (!m_returnValue)
    {
        throw std::runtime_error("Return value expression is null");
    }
}

const ExpressionPtr& FReturnStatement::GetReturnValue() const
{
    return m_returnValue;
}

void FReturnStatement::Execute(const FContext& context) const
{
    if (!m_returnValue)
    {
        throw std::runtime_error("Return value expression is null");
    }

    // Evaluate the return value expression in the given context
    ValuePtr returnValue = m_returnValue->Evaluate(context);

    // Set the return value in the context
    context.SetReturnValue(returnValue);
}
