/**
 * @file class_declaration_statement.hpp
 * @brief Declaration of the class declaration statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the header file for the block statement class
#include "statement/block/block_statement.hpp"

#include <string>
#include <vector>

/**
 * @brief Represents a class declaration statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * declares a class with its attributes and methods.
 */
class FClassDeclarationStatement final : public IStatement
{
    // The name of the class
    std::string m_className;

    // The name of the parent class, if any
    std::string m_parentClassName;

    // The list of interfaces implemented by the class
    std::vector<std::string> m_interfaces;

    // The list of traits used by the class
    std::vector<std::string> m_traits;

    // The block containing class attributes and methods
    BlockStatementPtr m_classBody;

public:

    /**
     * @brief Constructs a class declaration statement with the given class name and body.
     * @param className The name of the class.
     * @param classBody The block containing class attributes and methods.
     */
    FClassDeclarationStatement(
        const std::string& className,
        BlockStatementPtr classBody,
        const std::string& parentClassName = "",
        const std::vector<std::string>& interfaces = {},
        const std::vector<std::string>& traits = {}
    );

    /**
     * @brief Executes this class declaration statement within the given context.
     * @param context The context in which to execute the class declaration statement.
     */
    virtual void Execute(const FContext& context) const override;

    /**
     * @brief Gets the name of the class.
     * @return The name of the class.
     */
    const std::string& GetClassName() const;

    /**
     * @brief Gets the name of the parent class.
     * @return The name of the parent class.
     */
    const std::string& GetParentClassName() const;

    /**
     * @brief Gets the list of interfaces implemented by the class.
     * @return The list of interfaces implemented by the class.
     */
    const std::vector<std::string>& GetInterfaces() const;

    /**
     * @brief Gets the list of traits used by the class.
     * @return The list of traits used by the class.
     */
    const std::vector<std::string>& GetTraits() const;

    /**
     * @brief Gets the block containing class attributes and methods.
     * @return The block containing class attributes and methods.
     */
    const BlockStatementPtr& GetClassBody() const;

private:

    ObjectValuePtr GetParentClass(const FContext& context) const;
};

// Define a smart pointer type for FClassDeclarationStatement
using ClassDeclarationStatementPtr = std::unique_ptr<FClassDeclarationStatement>;
