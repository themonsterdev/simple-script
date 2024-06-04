/**
 * @file context.cpp
 * @brief Implementation of the context class.
 */

#include "context.hpp"  // Include the context header file
#include <stdexcept>    // For std::runtime_error

// Include the invokable function header file
#include "function/invokable_function.hpp" 
#include "builtin_function/builtin_function_registry.hpp"

FContext::FContext()
    // Create a new scope and append it to the end of the deque
    : m_scopes({ std::make_shared<FScope>() })
    , m_returnValue(Value())
    , m_hasReturnValue(false)
    , m_continueFlag(false)
    , m_throwFlag(false)
{
    RegisterBuiltinFunctions(*this);
}

void FContext::EnterScope() const
{
    // Create a new scope and append it to the end of the deque
	m_scopes.push_back(std::make_shared<FScope>());
}

void FContext::LeaveScope() const
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
        if (m_scopes.back()->IsVariableDeclared(name))
        {
            throw std::runtime_error("Variable '" + name + "' already declared in current scope");
        }

        // Add the variable to the current scope
        m_scopes.back()->DeclareVariable(name);
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
        if (m_scopes.back()->IsVariableDeclared(name))
        {
            // Assign the value to the variable in the current scope
            m_scopes.back()->AssignVariable(name, value);
        }
        else
        {
            // Check if the variable is a global variable
            if (m_scopes.front()->IsVariableDeclared(name))
            {
                // Assign the value to the global variable
                m_scopes.front()->AssignVariable(name, value);
            }
            else
            {
                throw std::runtime_error("Variable '" + name + "' not declared");
            }
        }
    }
    else
    {
        throw std::runtime_error("No scope available to assign variable");
    }
}

bool FContext::IsVariableDeclared(const std::string& name) const
{
    // Check if the variable is declared in the global scope
    if (!m_scopes.empty() && m_scopes.front()->IsVariableDeclared(name))
    {
        return true;
    }

    // Check if the variable is declared in any of the local scopes
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        if ((*it)->IsVariableDeclared(name)) {
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
        if ((*it)->IsVariableDeclared(name))
        {
            // Return the value of the variable if found in the current scope
            return (*it)->GetVariable(name);
        }
    }
    throw std::runtime_error("Undefined variable: " + name);
}

void FContext::RegisterFunction(const std::string& name, std::shared_ptr<FInvokableFunction> function) const
{
    if (!m_scopes.empty())
    {
        m_scopes.back()->RegisterFunction(name, std::move(function));
    }
    else
    {
        throw std::runtime_error("No scope to register function");
    }
}

Value FContext::CallFunction(const std::string& name, const std::vector<Value>& arguments) const
{
    for (const auto& scope : m_scopes)
    {
        if (scope->IsFunctionDeclared(name))
        {
            auto function = scope->GetFunction(name);
            Value result = function->Invoke(arguments, *this);
            return result;
        }
    }
    throw std::runtime_error("Function not declared: " + name);
}

void FContext::SetReturnValue(const Value& returnValue) const
{
    m_returnValue = returnValue;
    m_hasReturnValue = true;
}

Value FContext::GetReturnValue() const
{
    if (m_hasReturnValue)
    {
        return m_returnValue;
    }
    else
    {
        throw std::runtime_error("No return value set");
    }
}

bool FContext::HasReturnValue() const
{
    return m_hasReturnValue;
}

void FContext::ResetReturnValue() const
{
    m_returnValue = Value();    // Reset the return value
    m_hasReturnValue = false;   // Reset the flag
}

void FContext::SetContinueFlag(bool flag) const
{
    m_continueFlag = flag;
}

bool FContext::GetContinueFlag() const
{
    return m_continueFlag;
}

void FContext::SetThrowFlag(bool flag) const
{
    m_throwFlag = flag;
}

bool FContext::GetThrowFlag() const
{
    return m_throwFlag;
}
