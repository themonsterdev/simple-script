/**
 * @file function_declaration_statement.cpp
 * @brief Implementation of the function declaration statement class.
 */

// Include the header file for the function statement class
#include "ast/statement/function/function_declaration_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "value/function_value.hpp"

FFunctionDeclarationStatement::FFunctionDeclarationStatement(
    FunctionDefinitionPtr functionDefinition)
    : m_functionDefinition(functionDefinition)
{}

void FFunctionDeclarationStatement::Execute(const FContext& context) const
{
    const auto& name = m_functionDefinition->GetFunctionName();
    const auto& value = std::make_shared<CFunctionValue>(m_functionDefinition);
    context.AddSymbol(name, value);
}

const FunctionDefinitionPtr& FFunctionDeclarationStatement::GetFunctionDefinition() const
{
    return m_functionDefinition;
}
