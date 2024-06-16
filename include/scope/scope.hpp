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

#include "value/interface/value.hpp"
#include "type/function/function_definition.hpp"
#include "type/oop/class_definition.hpp"

using VariableMap = std::unordered_map<std::string, ValuePtr>;
using FunctionMap = std::unordered_map<std::string, FunctionDefinitionPtr>;
using ClassMap    = std::unordered_map<std::string, ClassDefinitionPtr>;
using EnumMap     = std::unordered_map<std::string, std::vector<std::string>>;
using SymbolMap   = std::unordered_map<std::string, ValuePtr>;

/**
 * @brief Represents a scope for storing variables and their values.
 *
 * This class manages variables within a scope and provides methods to add, retrieve, and remove variables.
 */
class FScope final
{
    // Symbol Tables
    VariableMap m_variables;
    FunctionMap m_functions;
    ClassMap    m_classes;
    EnumMap     m_enums;

    SymbolMap m_symbols;

    std::string m_lastClass;

public:

    void AddSymbol(const std::string& name, const ValuePtr& value);
    bool IsSymbolDeclared(const std::string& name) const;
    ValuePtr GetSymbol(const std::string& name) const;

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

    void DeclareFunction(FunctionDefinitionPtr function);
    bool IsFunctionDeclared(const std::string& name) const;
    FunctionDefinitionPtr GetFunction(const std::string& name) const;

    void DeclareClass(Visibility visibility, ClassDefinitionPtr classDefinition);
    void DeclareClassProperty(Visibility visibility, ClassPropertyDefinitionPtr propertyDefinition) const;
    void DeclareClassMethod(Visibility visibility, ClassMethodDefinitionPtr methodDefinition) const;
    ClassDefinitionPtr GetClassDefinition(const std::string& name) const;
    bool IsClassDeclared(const std::string& name) const;
};

using ScopePtr   = std::shared_ptr<FScope>;
using ScopeDeque = std::deque<ScopePtr>;
