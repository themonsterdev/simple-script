/**
 * @file scope.cpp
 * @brief Implementation of the FScope class.
 */

#include "scope.hpp"    // Include for the FScope class declaration
#include <stdexcept>    // Include for std::runtime_error

void FScope::AddVariable(const std::string& name)
{
    // Add the variable to the scope with a default-initialized value
    m_variables[name] = Value(); // Initialize with default value
}

void FScope::SetVariable(const std::string& name, Value value)
{
    // Set the value of the variable
    m_variables[name] = value;
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

bool FScope::HasVariable(const std::string& name) const
{
    // Check if the variable exists in the scope
    return m_variables.find(name) != m_variables.end();
}

void FScope::RemoveVariable(const std::string& name)
{
    // Remove the variable from the scope
    m_variables.erase(name);
}
