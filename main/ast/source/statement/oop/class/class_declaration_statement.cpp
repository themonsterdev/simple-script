/**
 * @file class_declaration_statement.cpp
 * @brief Implementation of the class declaration statement class.
 */

// Include the header file for the class declaration statement class
#include "statement/oop/class/class_declaration_statement.hpp"

// Include declarations for context objects
#include "context.hpp"
#include <stdexcept>

// Constructor definition
FClassDeclarationStatement::FClassDeclarationStatement(
    const std::string& className,
    BlockStatementPtr classBody,
    const std::string& parentClassName,
    const std::vector<std::string>& interfaces,
    const std::vector<std::string>& traits)
    : m_className(className)
    , m_classBody(std::move(classBody))
    , m_parentClassName(parentClassName)
    , m_interfaces(interfaces)
    , m_traits(traits)
{}

// Execute method definition
void FClassDeclarationStatement::Execute(const FContext& context) const
{
    const auto& parentClass = GetParentClass(context);

    const auto& objectValue = std::make_shared<FObjectValue>(m_className, parentClass);

    // Execute the block containing class attributes and methods
    // within the context
    if (m_classBody)
    {
        // store current class
        const auto& previousObject = context.GetCurrentClass();

        context.SetCurrentClass(objectValue);

        m_classBody->Execute(context);

        // reset current class for the continue statements with
        // previous classe if not ending
        context.SetCurrentClass(previousObject);
    }

    context.RegisterClass(m_className, objectValue);
}

const std::string& FClassDeclarationStatement::GetClassName() const
{
    return m_className;
}

const std::string& FClassDeclarationStatement::GetParentClassName() const
{
    return m_parentClassName;
}

const std::vector<std::string>& FClassDeclarationStatement::GetInterfaces() const
{
    return m_interfaces;
}

const std::vector<std::string>& FClassDeclarationStatement::GetTraits() const
{
    return m_traits;
}

const BlockStatementPtr& FClassDeclarationStatement::GetClassBody() const
{
    return m_classBody;
}

ObjectValuePtr FClassDeclarationStatement::GetParentClass(const FContext& context) const
{
    if (m_parentClassName.empty())
    {
        return nullptr;
    }

    if (!context.IsClassDeclared(m_parentClassName))
    {
        throw std::runtime_error("Parent class is not declared");
    }

    return context.GetClass(m_parentClassName);
}
