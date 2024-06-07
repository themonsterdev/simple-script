/**
 * @file trait_declaration_statement.hpp
 * @brief Declaration of the trait declaration statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the header file for the block statement trait
#include "statement/block/block_statement.hpp"

#include <string>
#include <vector>

/**
 * @brief Represents a trait declaration statement in the abstract syntax tree.
 *
 * This trait inherits from the IStatement interface and represents a statement that
 * declares a trait with its attributes and methods.
 */
class FTraitDeclarationStatement final : public IStatement
{
    // The name of the trait
    std::string m_traitName;

    // The block containing trait attributes and methods
    StatementPtr m_traitBody;

public:

    /**
     * @brief Constructs a trait declaration statement with the given class name and body.
     * @param traitName The name of the trait.
     * @param traitBody The block containing trait attributes and methods.
     */
    FTraitDeclarationStatement(
        const std::string& traitName,
        StatementPtr traitBody
    );

    /**
     * @brief Executes this trait declaration statement within the given context.
     * @param context The context in which to execute the trait declaration statement.
     */
    virtual void Execute(const FContext& context) const override;

    /**
     * @brief Gets the name of the trait.
     * @return The name of the trait.
     */
    const std::string& GetTraitName() const;

    /**
     * @brief Gets the block containing trait attributes and methods.
     * @return The block containing trait attributes and methods.
     */
    const StatementPtr& GetTraitBody() const;
};
