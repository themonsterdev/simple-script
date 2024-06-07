/**
 * @file scope.cpp
 * @brief Implementation of the FScope class.
 */

#include "scope.hpp"    // Include for the FScope class declaration
#include <stdexcept>    // Include for std::runtime_error

void FScope::DeclareVariable(const std::string& name)
{
    if (IsVariableDeclared(name))
    {
        throw std::runtime_error("Variable already declared: " + name);
    }

    // Default initialization
    m_variables[name] = nullptr;
}

void FScope::AssignVariable(const std::string& name, const ValuePtr& value)
{
    if (!IsVariableDeclared(name))
    {
        throw std::runtime_error("Variable not declared: " + name);
    }

    m_variables[name] = value;
}

bool FScope::IsVariableDeclared(const std::string& name) const
{
    return m_variables.find(name) != m_variables.end();
}

void FScope::SetVariable(const std::string& name, const ValuePtr& value)
{
    DeclareVariable(name);
    AssignVariable(name, value);
}

ValuePtr FScope::GetVariable(const std::string& name) const
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

void FScope::RegisterFunction(const std::string& name, FunctionValuePtr function)
{
    if (IsFunctionDeclared(name))
    {
        throw std::runtime_error("Function already declared: " + name);
    }

    m_functions[name] = std::move(function);
}

bool FScope::IsFunctionDeclared(const std::string& name) const
{
    return m_functions.find(name) != m_functions.end();
}

FunctionValuePtr FScope::GetFunction(const std::string& name) const
{
    auto it = m_functions.find(name);
    if (it != m_functions.end())
    {
        return it->second;
    }
   
    throw std::runtime_error("Function not declared: " + name);
}

void FScope::RegisterClass(const std::string& name, ObjectValuePtr object)
{
    if (IsClassDeclared(name))
    {
        throw std::runtime_error("Class '" + name + "' is already declared in this scope");
    }

    m_classes[name] = std::move(object);
}

bool FScope::IsClassDeclared(const std::string& name) const
{
    return m_classes.find(name) != m_classes.end();
}

ObjectValuePtr FScope::GetClass(const std::string& name) const
{
    auto it = m_classes.find(name);
    if (it != m_classes.end())
    {
        return it->second;
    }

    throw std::runtime_error("Class '" + name + "' not found in this scope");
}

bool FScope::IsClassContext() const
{
    return m_isClassContext;
}

void FScope::DeclareMethod(const std::string& name, FunctionValuePtr method)
{
    if (IsMethodDeclared(name))
    {
        throw std::runtime_error("Method '" + name + "' is already declared in this scope");
    }

    m_methods[name] = method;
    m_isClassContext = true;
}

bool FScope::IsMethodDeclared(const std::string& name) const
{
    return m_methods.find(name) != m_methods.end();
}

FunctionValuePtr FScope::GetMethod(const std::string& name) const
{
    auto it = m_methods.find(name);
    if (it != m_methods.end())
    {
        return it->second;
    }
    throw std::runtime_error("Method not declared: " + name);
}
