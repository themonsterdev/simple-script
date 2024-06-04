/**
 * @file scope.cpp
 * @brief Implementation of the FScope class.
 */

#include "scope.hpp"    // Include for the FScope class declaration
#include <stdexcept>    // Include for std::runtime_error

void FScope::DeclareVariable(const std::string& name)
{
    if (m_variables.find(name) == m_variables.end())
    {
        m_variables[name] = Value(); // Default initialization
    }
    else
    {
        throw std::runtime_error("Variable already declared: " + name);
    }
}

void FScope::AssignVariable(const std::string& name, const Value& value)
{
    if (IsVariableDeclared(name))
    {
        m_variables[name] = value;
    }
    else
    {
        throw std::runtime_error("Variable not declared: " + name);
    }
}

bool FScope::IsVariableDeclared(const std::string& name) const
{
    return m_variables.find(name) != m_variables.end();
}

void FScope::SetVariable(const std::string& name, const Value& value)
{
    DeclareVariable(name);
    AssignVariable(name, value);
}

Value FScope::GetVariable(const std::string& name) const
{
    // Check if the variable exists in the scope
    auto it = m_variables.find(name);
    if (it != m_variables.end())
    {
        // Return the value of the variable if found
        return it->second;
    }

    // Throw an exception if the variable is not found
    throw std::runtime_error("Undefined variable: " + name);
}

void FScope::RemoveVariable(const std::string& name)
{
    // Remove the variable from the scope
    m_variables.erase(name);
}

void FScope::RegisterFunction(const std::string& name, std::shared_ptr<FInvokableFunction> function)
{
    if (m_functions.find(name) == m_functions.end())
    {
        m_functions[name] = std::move(function);
    }
    else
    {
        throw std::runtime_error("Function already declared: " + name);
    }
}

bool FScope::IsFunctionDeclared(const std::string& name) const
{
    return m_functions.find(name) != m_functions.end();
}

std::shared_ptr<FInvokableFunction> FScope::GetFunction(const std::string& name) const
{
    auto it = m_functions.find(name);
    if (it != m_functions.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("Function not declared: " + name);
    }
}
