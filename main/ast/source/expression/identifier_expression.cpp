/**
 * @file identifier_expression.cpp
 * @brief Implementation of the identifier expression class.
 */

// Include the header file for the FIdentifierExpression class
#include "expression/identifier_expression.hpp"

FIdentifierExpression::FIdentifierExpression(const std::string& name)
    // Initialize the name member with the provided name
    : m_name(name)
{}

const std::string& FIdentifierExpression::GetName() const
{
    // Return the name of the identifier
    return m_name;
}

void FIdentifierExpression::SetName(const std::string& name)
{
    // Set the name of the identifier to the provided name
    m_name = name;
}

Value FIdentifierExpression::Evaluate(const FContext& context) const
{
    // Retrieve the value associated with the identifier from the context
    return context.GetVariable(m_name);
}
