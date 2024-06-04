/**
 * @file scope.hpp
 * @brief Declaration of the FScope class.
 */

// Ensure this file is included only once
#pragma once

#include <variant>          // Include for std::variant
#include <unordered_map>    // Include for std::unordered_map
#include <string>           // Include for std::string
#include <vector>           // Include for std::vector
#include <memory>           // Include for memory

#include "function/invokable_function.hpp"

// Define a variant type to represent different possible values
using Value = std::variant<bool, int, std::string>;

/**
 * @brief Represents a scope for storing variables and their values.
 *
 * This class manages variables within a scope and provides methods to add, retrieve, and remove variables.
 */
class FScope final
{
    // Map to store variable names and their corresponding values
	std::unordered_map<std::string, Value> m_variables;

    // Map of function names to invokable functions
    std::unordered_map<std::string, std::shared_ptr<FInvokableFunction>> m_functions;

public:

    /**
     * @brief Declares a variable in the current scope.
     * @param name The name of the variable to declare.
     */
    void DeclareVariable(const std::string& name);

    /**
     * @brief Assigns a value to a variable in the current scope.
     * @param name The name of the variable to assign.
     * @param value The value to assign to the variable.
     */
    void AssignVariable(const std::string& name, const Value& value);

    /**
     * @brief Checks if a variable is declared in the current scope.
     * @param name The name of the variable to check.
     * @return True if the variable is declared, false otherwise.
     */
    bool IsVariableDeclared(const std::string& name) const;

    /**
     * @brief Sets the value of a variable in the current scope.
     * @param name The name of the variable to set.
     * @param value The value to set for the variable.
     */
    void SetVariable(const std::string& name, const Value& value);

    /**
     * @brief Gets the value of a variable from the current scope.
     * @param name The name of the variable to retrieve.
     * @return The value of the variable.
     */
    Value GetVariable(const std::string& name) const;

    /**
     * @brief Removes the variable with the given name from the scope.
     * @param name The name of the variable to remove.
     */
    void RemoveVariable(const std::string& name);
    
    /**
     * @brief Checks if a variable with the given name exists in the scope and is of the specified type.
     * @tparam T The type to check against.
     * @param name The name of the variable to check.
     * @return true if the variable exists and is of the specified type, false otherwise.
     */
    template<typename T>
    bool IsVariableOfType(const std::string& name) const;

    /**
     * @brief Registers a function in the current scope.
     * @param name The name of the function to register.
     * @param function The invokable function to register.
     */
    void RegisterFunction(const std::string& name, std::shared_ptr<FInvokableFunction> function);

    /**
     * @brief Checks if a function is declared in the current scope.
     * @param name The name of the function to check.
     * @return True if the function is declared, false otherwise.
     */
    bool IsFunctionDeclared(const std::string& name) const;

    /**
     * @brief Gets the invokable function from the current scope.
     * @param name The name of the function to retrieve.
     * @return The invokable function.
     */
    std::shared_ptr<FInvokableFunction> GetFunction(const std::string& name) const;
};

/**
 * @brief Checks if a variable with the given name exists in the scope and is of the specified type.
 *
 * @tparam T The type to check against.
 * @param name The name of the variable to check.
 * @return true if the variable exists and is of the specified type, false otherwise.
 */
template<typename T>
bool FScope::IsVariableOfType(const std::string& name) const
{
    auto it = m_variables.find(name);
    if (it != m_variables.end())
    {
        // Check if the value stored in the variable matches the specified type
        return std::holds_alternative<T>(it->second);
    }

    // The variable does not exist
    return false;
}
