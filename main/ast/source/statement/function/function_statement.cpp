/**
 * @file function_statement.cpp
 * @brief Implementation of the function statement class.
 */

// Include the header file for the function statement class
#include "statement/function/function_statement.hpp"

#include <vector>
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

// Constructor definition
FFunctionStatement::FFunctionStatement(std::string name, FunctionParameters parameters, StatementPtr body)
    // Initialize m_name with the given name
    : m_name(name)
    // Initialize m_parameters with the given parameters
    , m_parameters(parameters)
    // Initialize m_body with the given body
    , m_body(std::move(body))
{}

// Execute method definition
void FFunctionStatement::Execute(const FContext& context) const
{
    const auto function = std::make_shared<FInvokableFunction>(m_name, m_parameters, m_body.get());
    
    if (function)
    {
        context.RegisterFunction(m_name, function);
    }
}

// GetName method definition
const std::string& FFunctionStatement::GetName() const
{
    // Return a constant reference to the name of the function
    return m_name;
}

// GetParameters method definition
const FunctionParameters& FFunctionStatement::GetParameters() const
{
    // Return a constant reference to the parameters of the function
    return m_parameters;
}

// GetBody method definition
const StatementPtr& FFunctionStatement::GetBody() const
{
    // Return a constant reference to the body of the function
    return m_body;
}
