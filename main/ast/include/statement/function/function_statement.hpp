/**
 * @file function_statement.hpp
 * @brief Declaration of the function statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"
#include <string>

// Define a type alias for function parameters
using FunctionParameters = std::vector<std::string>;

/**
 * @brief Represents a function declaration statement in the abstract syntax tree.
 *
 * This class inherits from the IStatement interface and represents a statement that
 * declares a function with a name, parameters, and a body.
 */
class FFunctionStatement : public IStatement
{
    // The name of the function
    std::string m_name;

    // The parameters of the function
    FunctionParameters m_parameters;

    // The body of the function
    StatementPtr m_body;

public:

    /**
     * @brief Constructs an FFunctionStatement with the given name, parameters, and body.
     * @param name The name of the function.
     * @param parameters The parameters of the function.
     * @param body The body of the function.
     */
    FFunctionStatement(std::string name, FunctionParameters parameters, StatementPtr body);

    /**
     * @brief Executes the function within the given context.
     *
     * This method executes the body of the function within the provided context.
     * @param context The context in which to execute the function.
     */
    virtual void Execute(const FContext& context) const override;

    /**
     * @brief Gets the name of the function.
     * @return The name of the function.
     */
    const std::string& GetName() const;

    /**
     * @brief Gets the parameters of the function.
     * @return The parameters of the function.
     */
    const FunctionParameters& GetParameters() const;

    /**
     * @brief Gets the body of the function.
     * @return The body of the function.
     */
    const StatementPtr& GetBody() const;
};
