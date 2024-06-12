/**
 * @file function_declaration_statement.cpp
 * @brief Implementation of the function declaration statement class.
 */

// Include the header file for the function statement class
#include "ast/statement/function/function_declaration_statement.hpp"

#include <vector>
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

FFunctionDeclarationStatement::FFunctionDeclarationStatement(FunctionDefinitionPtr functionDefinition)
    : m_functionDefinition(functionDefinition)
{}

void FFunctionDeclarationStatement::Execute(const FContext& context) const
{
    context.DeclareFunction(m_functionDefinition);
}

const FunctionDefinitionPtr& FFunctionDeclarationStatement::GetFunctionDefinition() const
{
    return m_functionDefinition;
}
