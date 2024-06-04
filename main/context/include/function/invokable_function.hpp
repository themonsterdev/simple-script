/**
 * @file invokable_function.hpp
 * @brief Declaration of the FInvokableFunction class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"

#include <string>
#include <vector>
#include <variant>

using FunctionParameters = std::vector<std::string>;
using Value = std::variant<bool, int, std::string>;

/**
 * @brief Represents a builtin function.
 */
class FInvokableFunction
{
protected:

    std::string m_name;
    FunctionParameters m_parameters;
    IStatement* m_body;

public:

    /**
     * @brief Constructs a builtin function.
     * @param name The name of the builtin function.
     * @param parameters The parameters for the builtin function.
     * @param function The function implementation.
     */
    FInvokableFunction(std::string name, FunctionParameters parameters, IStatement* body);

    /**
     * @brief Invokes the builtin function.
     * @param arguments The arguments for the function.
     * @param context The current execution context.
     * @return The result of the function call.
     */
    virtual Value Invoke(const std::vector<Value>& arguments, const FContext& context) const;

    std::string GetName() const;
};
