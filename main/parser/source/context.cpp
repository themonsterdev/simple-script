#include "context.hpp"
#include <stdexcept>

FContext::FContext()
{
    // Create a new scope and append it to the end of the deque
	m_scopes.push_back(std::make_shared<FScope>());
}

void FContext::EnterScope()
{
    // Create a new scope and append it to the end of the deque
	m_scopes.push_back(std::make_shared<FScope>());
}

void FContext::LeaveScope()
{
    // Check if there are more than one scope in the deque
    if (m_scopes.size() > 1)
    {
        // Pop the top scope from the deque
        m_scopes.pop_back();
    }
    else
    {
        throw std::runtime_error("Cannot leave global scope");
    }
}

void FContext::DeclareVariable(const std::string& name) const
{
    // Check if there is at least one scope available
    if (!m_scopes.empty())
    {
        // Check if the variable is already declared in the current scope
        if (m_scopes.back()->HasVariable(name))
        {
            throw std::runtime_error("Variable '" + name + "' already declared in current scope");
        }

        // Add the variable to the current scope
        m_scopes.back()->AddVariable(name);
    }
    else
    {
        throw std::runtime_error("No scope available to declare variable");
    }
}

void FContext::AssignVariable(const std::string& name, const Value& value) const
{
    // Check if there is at least one scope available
    if (!m_scopes.empty())
    {
        // Check if the variable is declared in the current scope
        if (m_scopes.back()->HasVariable(name))
        {
            // Assign the value to the variable in the current scope
            m_scopes.back()->SetVariable(name, value);
        }
        else
        {
            throw std::runtime_error("Variable '" + name + "' not declared in current scope");
        }
    }
    else
    {
        throw std::runtime_error("No scope available to assign variable");
    }
}

bool FContext::IsVariableDeclared(const std::string& name) const
{
    // Iterate through the scopes from the end to the beginning
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the variable exists in the current scope
        if ((*it)->HasVariable(name))
        {
            // Return true if the variable is found in the current scope
            return true;
        }
    }

    return false;
}

void FContext::SetVariable(const std::string& name, const Value& value) const
{
    // Set the variable in the top scope of the deque
    m_scopes.back()->SetVariable(name, value);
}

Value FContext::GetVariable(const std::string& name) const
{
    // Iterate through the scopes from the end to the beginning
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the variable exists in the current scope
        if ((*it)->HasVariable(name))
        {
            // Return the value of the variable if found in the current scope
            return (*it)->GetVariable(name);
        }
    }
    throw std::runtime_error("Undefined variable: " + name);
}
