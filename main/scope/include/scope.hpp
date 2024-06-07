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
#include <deque>            // Include for deque

#include "statement/function/function_parameter.hpp"
#include "function_value.hpp"
#include "object_value.hpp"

using VariableMap = std::unordered_map<std::string, ValuePtr>;
using FunctionMap = std::unordered_map<std::string, FunctionValuePtr>;
using ClassMap    = std::unordered_map<std::string, ObjectValuePtr>;

/**
 * @brief Represents a scope for storing variables and their values.
 *
 * This class manages variables within a scope and provides methods to add, retrieve, and remove variables.
 */
class FScope final
{
    VariableMap m_variables;
    FunctionMap m_functions;
    FunctionMap m_methods;
    ClassMap m_classes;

    // Indicates if the current scope is a class context
    bool m_isClassContext = false;

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
    void AssignVariable(const std::string& name, const ValuePtr& value);

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
    void SetVariable(const std::string& name, const ValuePtr& value);

    /**
     * @brief Gets the value of a variable from the current scope.
     * @param name The name of the variable to retrieve.
     * @return The value of the variable.
     */
    ValuePtr GetVariable(const std::string& name) const;

    /**
     * @brief Removes the variable with the given name from the scope.
     * @param name The name of the variable to remove.
     */
    void RemoveVariable(const std::string& name);

    /**
     * @brief Registers a function in the current scope.
     * @param name The name of the function to register.
     * @param function The invokable function to register.
     */
    void RegisterFunction(const std::string& name, FunctionValuePtr function);

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
    FunctionValuePtr GetFunction(const std::string& name) const;

    void RegisterClass(const std::string& name, ObjectValuePtr object);
    bool IsClassDeclared(const std::string& name) const; 
    ObjectValuePtr GetClass(const std::string& name) const;

    void DeclareMethod(const std::string& name, FunctionValuePtr method);
    bool IsClassContext() const;
    bool IsMethodDeclared(const std::string& name) const;
    FunctionValuePtr GetMethod(const std::string& name) const;
};

using ScopePtr   = std::shared_ptr<FScope>;
using ScopeDeque = std::deque<ScopePtr>;
