/**
 * @file function_declaration_statement.hpp
 * @brief Declaration of the function declaration statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

#include "function/function_definition.hpp"

/**
 * @brief Represents a function declaration statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * declares a function with a name, parameters, and a body.
 */
class FFunctionDeclarationStatement : public IStatement
{
    FunctionDefinitionPtr m_functionDefinition;

public:

    FFunctionDeclarationStatement(FunctionDefinitionPtr functionDefinition);

    virtual void Execute(const FContext& context) const override;

    const FunctionDefinitionPtr& GetFunctionDefinition() const;
};
