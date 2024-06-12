/**
 * @file scope.cpp
 * @brief Implementation of the FScope class.
 */

#include "scope/scope.hpp"    // Include for the FScope class declaration

#include "value/function_value.hpp"
#include "value/number_value.hpp"

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

void FScope::DeclareFunction(FunctionDefinitionPtr function)
{
    const auto& name = function->GetName();

    if (IsFunctionDeclared(name))
    {
        throw std::runtime_error("Function already declared: " + name);
    }

    m_functions[name] = function;
}

bool FScope::IsFunctionDeclared(const std::string& name) const
{
    return m_functions.find(name) != m_functions.end();
}

FunctionDefinitionPtr FScope::GetFunction(const std::string& name) const
{
    auto it = m_functions.find(name);
    if (it != m_functions.end())
    {
        return it->second;
    }
   
    throw std::runtime_error("Function not declared: " + name);
}

void FScope::DeclareClass(Visibility visibility, ClassDefinitionPtr classDefinition)
{
    auto& className = classDefinition->GetName();

    if (IsClassDeclared(className))
    {
        throw std::runtime_error("Class '" + className + "' is already declared in this scope");
    }

    m_classes[className] = classDefinition;
    m_lastClass          = className;
}

void FScope::DeclareClassProperty(Visibility visibility, ClassPropertyDefinitionPtr propertyDefinition) const
{
    const auto& lastClassDefinition = GetClassDefinition(m_lastClass);
    lastClassDefinition->AddProperty(visibility, propertyDefinition);
}

void FScope::DeclareClassMethod(Visibility visibility, ClassMethodDefinitionPtr methodDefinition) const
{
    const auto& lastClassDefinition = GetClassDefinition(m_lastClass);
    lastClassDefinition->AddMethod(visibility, methodDefinition);
}

ClassDefinitionPtr FScope::GetClassDefinition(const std::string& name) const
{
    auto it = m_classes.find(name);
    if (it != m_classes.end())
    {
        return it->second;
    }
    throw std::runtime_error("Class not declared: " + name);
}

bool FScope::IsClassDeclared(const std::string& name) const
{
    return m_classes.find(name) != m_classes.end();
}
