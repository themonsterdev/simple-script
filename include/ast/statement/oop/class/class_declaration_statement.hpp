/**
 * @file class_declaration_statement.hpp
 * @brief Declaration of the class declaration statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "ast/statement/interface/statement.hpp"

#include "type/oop/class_definition.hpp"

/**
 * @brief Represents a class declaration statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * declares a class with its attributes and methods.
 */
class FClassDeclarationStatement final : public IStatement
{
    ClassDefinitionPtr m_classDefinition;

    // The block containing class attributes and methods
    StatementPtr m_classBody;

public:

    FClassDeclarationStatement(
        ClassDefinitionPtr classDefinition,
        StatementPtr classBody
    );

    /**
     * @brief Executes this class declaration statement within the given context.
     * @param context The context in which to execute the class declaration statement.
     */
    void Execute(const FContext& context) const override;

    ClassDefinitionPtr GetClassDefinition() const;

    const StatementPtr& GetClassBody() const;
};

// Define a smart pointer type for FClassDeclarationStatement
using ClassDeclarationStatementPtr = std::unique_ptr<FClassDeclarationStatement>;
