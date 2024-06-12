/**
 * @file identifier_expression.cpp
 * @brief Implementation of the identifier expression class.
 */

// Include the header file for the FIdentifierExpression class
#include "ast/expression/identifier_expression.hpp"
#include "value/function_value.hpp"

// Include declarations for context objects
#include "context/context.hpp"

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

ValuePtr FIdentifierExpression::Evaluate(const FContext& context) const
{
    if (context.IsFunctionDeclared(m_name))
    {
        const auto& functionDefinition = context.GetFunction(m_name);
        return std::make_unique<CFunctionValue>(functionDefinition);
    }

    // Retrieve the value associated with the identifier from the context
    return context.GetVariable(m_name);
}
