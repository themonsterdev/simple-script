/**
 * @file scope.hpp
 * @brief Declaration of the FScope class.
 */

#pragma once

#include <variant>          // Include for std::variant
#include <unordered_map>    // Include for std::unordered_map
#include <string>           // Include for std::string

// Define a variant type to represent different possible values
using Value = std::variant<int, std::string>;

/**
 * @brief Represents a scope for storing variables and their values.
 *
 * This class manages variables within a scope and provides methods to add, retrieve, and remove variables.
 */
class FScope final
{
    // Map to store variable names and their corresponding values
	std::unordered_map<std::string, Value> m_variables;

public:

    /**
     * @brief Adds a variable to the scope with the given name.
     * @param name The name of the variable to add.
     */
    void AddVariable(const std::string& name);

    /**
     * @brief Sets the value of the variable with the given name.
     * @param name The name of the variable to set.
     * @param value The value to set for the variable.
     */
    void SetVariable(const std::string& name, Value value);

    /**
     * @brief Gets the value of the variable with the given name.
     * @param name The name of the variable to get.
     * @return The value of the variable.
     * @throw std::runtime_error if the variable does not exist.
     */
    Value GetVariable(const std::string& name) const;

    /**
     * @brief Checks if a variable with the given name exists in the scope.
     * @param name The name of the variable to check.
     * @return true if the variable exists, false otherwise.
     */
    bool HasVariable(const std::string& name) const;

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
