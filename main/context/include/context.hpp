/**
 * @file context.hpp
 * @brief Declaration of the context class.
 */

// Ensure this file is included only once
#pragma once

#include <deque>        // For std::deque
#include <memory>       // For std::shared_ptr
#include "scope.hpp"    // Include declarations for scope objects

/**
 * @brief Represents the context for variable declarations and assignments.
 *
 * This class manages variable scopes and provides methods to declare, assign,
 * and access variables within those scopes.
 */
class FContext final
{
    // Deque of scopes
	std::deque<std::shared_ptr<FScope>> m_scopes;

public:

    /**
     * @brief Constructs a new context.
     */
    FContext();

    /**
     * @brief Enters a new scope.
     */
    void EnterScope();

    /**
     * @brief Leaves the current scope.
     */
    void LeaveScope();

    /**
     * @brief Declares a variable in the current scope.
     * @param name The name of the variable to declare.
     */
    void DeclareVariable(const std::string& name) const;

    /**
     * @brief Assigns a value to a variable in the current scope.
     * @param name The name of the variable to assign.
     * @param value The value to assign to the variable.
     */
    void AssignVariable(const std::string& name, const Value& value) const;

    /**
     * @brief Checks if a variable is declared in any of the scopes.
     * @param name The name of the variable to check.
     * @return True if the variable is declared, false otherwise.
     */
    bool IsVariableDeclared(const std::string& name) const;

    /**
     * @brief Sets the value of a variable in the current scope.
     * @param name The name of the variable to set.
     * @param value The value to set for the variable.
     */
    void SetVariable(const std::string& name, const Value& value) const;

    /**
     * @brief Gets the value of a variable from the current scope.
     * @param name The name of the variable to retrieve.
     * @return The value of the variable.
     */
    Value GetVariable(const std::string& name) const;
};
