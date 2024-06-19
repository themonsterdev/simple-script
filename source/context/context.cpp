/**
 * @file context.cpp
 * @brief Implementation of the context class.
 */

#include "context/context.hpp"  // Include the context header file
#include <stdexcept>    // For std::runtime_error

// Include the invokable function header file
#include "context/builtin_function/builtin_function_registry.hpp"
#include "value/function_value.hpp"
#include "value/class_value.hpp"

FContext::FContext()
    // Create a new scope and append it to the end of the deque
    : m_scopes({})
    , m_returnValue(nullptr)
    , m_hasReturnValue(false)
    , m_continueFlag(false)
    , m_throwFlag(false)

    , m_currentClass(nullptr)
    , m_hasCurrentClass(false)
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

void FContext::AddSymbol(const std::string& name, const ValuePtr& value) const
{
    if (m_hasCurrentClass)
    {
        const auto& object = std::dynamic_pointer_cast<FClassValue>(m_currentClass);

        if (object)
        {
            object->AddMember(name, value);
        }
        return;
    }

    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to add symbol");
    }

    currentScope->AddSymbol(name, value);
}

bool FContext::IsSymbolDeclared(const std::string& name) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the symbol exists in the current scope
        if ((*it)->IsSymbolDeclared(name))
        {
            return true;
        }
    }

    return false;
}

ValuePtr FContext::GetSymbol(const std::string& name) const
{
    if (HasCurrentClass())
    {
        const auto& symbol = GetCurrentClass();
        const auto& object = std::dynamic_pointer_cast<FClassValue>(symbol);

        if (object->HasMember(name))
        {
            return object->GetMember(name);
        }
    }

    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        // Check if the symbol exists in the current scope
        if ((*it)->IsSymbolDeclared(name))
        {
            return (*it)->GetSymbol(name);
        }
    }

    throw std::runtime_error("Undefined symbol: " + name);
}

void FContext::DeclareSymbol(const std::string& name) const
{
    auto currentScope = GetCurrentScope();

    if (currentScope == nullptr)
    {
        throw std::runtime_error("No scope available to declare symbol");
    }

    currentScope->DeclareSymbol(name);
}

void FContext::AssignSymbol(const std::string& name, const ValuePtr& value) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        if ((*it)->IsSymbolDeclared(name))
        {
            // Assign the value to the symbol in the current scope
            (*it)->AssignSymbol(name, value);

            return;
        }
    }

    // If the symbol is not found in any scope, throw an error
    throw std::runtime_error("Symbol '" + name + "' not declared");
}

ValuePtr FContext::Call(const std::string& name, const std::vector<ValuePtr>& arguments) const
{
    // Traverse the scopes from the most recent to the oldest
    for (auto it = m_scopes.rbegin(); it != m_scopes.rend(); ++it)
    {
        const auto& scope = *it;

        // Check if the function exists in the current scope
        if (scope->IsSymbolDeclared(name))
        {
            const auto& symbol = scope->GetSymbol(name);
            if (symbol)
            {
                return symbol->CallMethod(*this, name, arguments);
            }
        }
    }

    throw std::runtime_error("Function not declared: " + name);
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

void FContext::SetCurrentClass(const ValuePtr& currentClass) const
{
    m_currentClass    = currentClass;
    m_hasCurrentClass = currentClass != nullptr;
}

ValuePtr FContext::GetCurrentClass() const
{
    return m_currentClass;
}

bool FContext::HasCurrentClass() const
{
    return m_hasCurrentClass;
}

void FContext::ResetCurrentClass() const
{
    m_currentClass = nullptr;  // Reset the current class
    m_hasCurrentClass = false; // Reset the flag
}
