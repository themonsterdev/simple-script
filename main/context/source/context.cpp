/**
 * @file context.cpp
 * @brief Implementation of the context class.
 */

#include "context.hpp"  // Include the context header file
#include <stdexcept>    // For std::runtime_error

// Include the invokable function header file
#include "builtin_function/builtin_function_registry.hpp"
#include "function_value.hpp"

FContext::FContext()
    // Create a new scope and append it to the end of the deque
    : m_scopes({})
    , m_returnValue(nullptr)
    , m_hasReturnValue(false)
    , m_continueFlag(false)
    , m_throwFlag(false)
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

void FContext::DeclareFunction(FunctionDefinitionPtr function) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to register function");
    }

    currentScope->DeclareFunction(function);
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

FunctionDefinitionPtr FContext::GetFunction(const std::string& name) const
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

ValuePtr FContext::Call(const std::string& name, const std::vector<ValuePtr>& arguments) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        const auto& scope = *it;

        // Check if the function exists in the current scope
        if (scope->IsVariableDeclared(name))
        {
            const auto& variable = scope->GetVariable(name);
            const auto& function = dynamic_cast<CFunctionValue*>(variable.get());
            if (function)
            {
                return function->Invoke(arguments, *this);
            }
            else
            {
                // throw
            }
        }

        // Check if the function exists in the current scope
        if (scope->IsFunctionDeclared(name))
        {
            const auto& function = scope->GetFunction(name);
            return function->Invoke(*this, arguments);
        }

        // Check if the class exists in the current scope
        if (scope->IsClassDeclared(name))
        {
            const auto& classDefinition = scope->GetClassDefinition(name);
            return classDefinition->NewInstance(*this, arguments);
        }
    }

    throw std::runtime_error("Function not declared: " + name);
}

void FContext::DeclareClass(Visibility visibility, ClassDefinitionPtr classDefinition) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to register class");
    }

    currentScope->DeclareClass(visibility, classDefinition);
}

void FContext::DeclareClassProperty(Visibility visibility, ClassPropertyDefinitionPtr propertyDefinition) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to declare property definition");
    }

    currentScope->DeclareClassProperty(visibility, propertyDefinition);
}

void FContext::DeclareClassMethod(Visibility visibility, ClassMethodDefinitionPtr methodDefinition) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to declare method definition");
    }

    currentScope->DeclareClassMethod(visibility, methodDefinition);
}

ClassDefinitionPtr FContext::GetClassDefinition(const std::string& name) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to get class definition");
    }

    return currentScope->GetClassDefinition(name);
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
