/**
 * @file context.cpp
 * @brief Implementation of the context class.
 */

#include "context.hpp"  // Include the context header file
#include <stdexcept>    // For std::runtime_error

// Include the invokable function header file
#include "builtin_function/builtin_function_registry.hpp"

FContext::FContext()
    // Create a new scope and append it to the end of the deque
    : m_scopes({})
    , m_returnValue(nullptr)
    , m_hasReturnValue(false)
    , m_continueFlag(false)
    , m_throwFlag(false)
    , m_currentClass(nullptr)
{
    EnterScope();
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

//////////////////////////////////////////////////////
// Scope current /////////////////////////////////////
//////////////////////////////////////////////////////

ScopePtr FContext::GetCurrentScope() const
{
    // Check if there is at least one scope available
    if (!m_scopes.empty())
    {
        return m_scopes.back();
    }
    
    return nullptr;
}

void FContext::DeclareVariable(const std::string& name) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to declare variable");
    }

    currentScope->DeclareVariable(name);
}

void FContext::SetVariable(const std::string& name, const ValuePtr& value) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to set variable");
    }

    // Set the variable in the top scope of the deque
    currentScope->SetVariable(name, value);
}

void FContext::RegisterFunction(const std::string& name, FunctionValuePtr function) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to register function");
    }

    currentScope->RegisterFunction(name, std::move(function));
}

void FContext::RegisterClass(const std::string& name, ObjectValuePtr object) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to register class");
    }

    currentScope->RegisterClass(name, std::move(object));
}

//////////////////////////////////////////////////////
// Current to top scope //////////////////////////////
//////////////////////////////////////////////////////

void FContext::AssignVariable(const std::string& name, const ValuePtr& value) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        if ((*it)->IsVariableDeclared(name))
        {
            // Assign the value to the variable in the current scope
            (*it)->AssignVariable(name, value);

            return;
        }
    }

    // If the variable is not found in any scope, throw an error
    throw std::runtime_error("Variable '" + name + "' not declared");
}

bool FContext::IsVariableDeclared(const std::string& name) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        if ((*it)->IsVariableDeclared(name))
        {
            return true;
        }
    }

    return false;
}

ValuePtr FContext::GetVariable(const std::string& name) const
{
    // Traverse the scopes from the most recent to the oldest
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

bool FContext::IsFunctionDeclared(const std::string& name) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the function exists in the current scope
        if ((*it)->IsFunctionDeclared(name))
        {
            return true;
        }
    }

    return false;
}

FunctionValuePtr FContext::GetFunction(const std::string& name) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the function exists in the current scope
        if ((*it)->IsFunctionDeclared(name))
        {
            return (*it)->GetFunction(name);
        }
    }

    throw std::runtime_error("Undefined function: " + name);
}

ValuePtr FContext::CallFunction(const std::string& name, const std::vector<ValuePtr>& arguments) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the function exists in the current scope
        if ((*it)->IsFunctionDeclared(name))
        {
            auto function = (*it)->GetFunction(name);
            return function->Invoke(arguments, *this);
        }
        // Check if the class exists in the current scope
        else if ((*it)->IsClassDeclared(name))
        {
            return (*it)->GetClass(name);
        }
    }

    throw std::runtime_error("Function not declared: " + name);
}

bool FContext::IsClassDeclared(const std::string& name) const
{
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        if ((*it)->IsClassDeclared(name))
        {
            return true;
        }
    }

    return false;
}

ObjectValuePtr FContext::GetClass(const std::string& name) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the class exists in the current scope
        if ((*it)->IsClassDeclared(name))
        {
            return (*it)->GetClass(name);
        }
    }

    throw std::runtime_error("Class not declared: " + name);
}

//////////////////////////////////////////////////////
// Method class statement ////////////////////////////
//////////////////////////////////////////////////////

void FContext::DeclareMethod(const std::string& name, FunctionValuePtr method) const
{
    
}

bool FContext::IsClassContext() const
{
    return false;
}

bool FContext::IsMethodDeclared(const std::string& name) const
{
    return false;
}

FunctionValuePtr FContext::GetMethod(const std::string& name) const
{
    return nullptr;
}

//////////////////////////////////////////////////////
// Return value statement ////////////////////////////
//////////////////////////////////////////////////////

void FContext::SetReturnValue(const ValuePtr& returnValue) const
{
    m_returnValue    = returnValue;
    m_hasReturnValue = true;
}
ValuePtr FContext::GetReturnValue() const
{
    if (!m_hasReturnValue)
    {
        throw std::runtime_error("No return value set");
    }

    return m_returnValue;
}
bool FContext::HasReturnValue() const
{
    return m_hasReturnValue;
}
void FContext::ResetReturnValue() const
{
    m_returnValue = nullptr;    // Reset the return value
    m_hasReturnValue = false;   // Reset the flag
}

//////////////////////////////////////////////////////
// continue statement ////////////////////////////////
//////////////////////////////////////////////////////

void FContext::SetContinueFlag(bool flag) const
{
    m_continueFlag = flag;
}
bool FContext::GetContinueFlag() const
{
    return m_continueFlag;
}

//////////////////////////////////////////////////////
// throw statement ///////////////////////////////////
//////////////////////////////////////////////////////

void FContext::SetThrowFlag(bool flag) const
{
    m_throwFlag = flag;
}
bool FContext::GetThrowFlag() const
{
    return m_throwFlag;
}

//////////////////////////////////////////////////////
// Declaration class statement ///////////////////////
//////////////////////////////////////////////////////

void FContext::SetCurrentClass(ObjectValuePtr object) const
{
    m_currentClass = object;
}
ObjectValuePtr FContext::GetCurrentClass() const
{
    return m_currentClass;
}

//////////////////////////////////////////////////////
// Access class //////////////////////////////////////
//////////////////////////////////////////////////////

bool FContext::IsDerivedFromClass(const FObjectValue* object) const
{
    if (!object || !m_currentClass)
    {
        return false;
    }

    return m_currentClass->IsDerivedFromClass(object);
}
bool FContext::IsSameClass(const FObjectValue* object) const
{
    if (m_currentClass)
    {
        return m_currentClass->IsSameClass(object);
    }
    return false;
}
