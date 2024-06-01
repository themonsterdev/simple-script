/**
 * @file var_declaration_list_statement.hpp
 * @brief Declaration of the FVarDeclarationListStatement class.
 */

// Ensure this file is included only once
#pragma once

// Include base class header
#include "statement/interface/statement.hpp"

/**
 * @brief Class for variable declaration list statements.
 * This class represents statements that declare multiple variables.
 */
class FVarDeclarationListStatement : public IStatement
{
    // The list of variable declarations.
    StatementVector m_declarations;

public:

    /**
     * @brief Constructs an FVarDeclarationListStatement object with the given list of declarations.
     * @param declarations The list of variable declarations.
     */
    FVarDeclarationListStatement(StatementVector declarations);

    /**
     * @brief Executes the variable declaration list statement.
     * @param context The execution context.
     */
    virtual void Execute(const FContext& context) const override;

    /**
     * @brief Gets the list of variable declarations.
     * @return The list of variable declarations.
     */
    const StatementVector& GetDeclarations() const;
};
