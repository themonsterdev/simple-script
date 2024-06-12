/**
 * @file context.hpp
 * @brief Declaration of the context class.
 */

// Ensure this file is included only once
#pragma once

#include <deque>        // For std::deque
#include <memory>       // For std::shared_ptr
#include "scope/scope.hpp"

/**
 * @brief Represents the context for variable declarations and assignments.
 *
 * This class manages variable scopes and provides methods to declare, assign,
 * and access variables within those scopes.
 */
class FContext final
{
    // Deque of scopes
    mutable ScopeDeque m_scopes;
    mutable ValuePtr m_returnValue;
    mutable bool m_hasReturnValue;
    mutable bool m_continueFlag;
    mutable bool m_throwFlag;

public:

    /**
     * @brief Constructs a new context.
     */
    FContext();

    /**
     * @brief Enters a new scope.
     */
    void EnterScope() const;

    /**
     * @brief Leaves the current scope.
     */
    void LeaveScope() const;

    //////////////////////////////////////////////////////
    // Current Scope /////////////////////////////////////
    //////////////////////////////////////////////////////

    /**
     * @brief Gets the current scope.
     * @return A pointer to the current scope.
     */
    ScopePtr GetCurrentScope() const;

    /**
     * @brief Declares a variable in the current scope.
     * @param name The name of the variable to declare.
     */
    void DeclareVariable(const std::string& name) const;

    /**
     * @brief Sets the value of a variable in the current scope.
     * @param name The name of the variable to set.
     * @param value The value to set for the variable.
     */
    void SetVariable(const std::string& name, const ValuePtr& value) const;

    void DeclareFunction(FunctionDefinitionPtr function) const;
    bool IsFunctionDeclared(const std::string& name) const;
    FunctionDefinitionPtr GetFunction(const std::string& name) const;

    void DeclareClass(Visibility visibility, ClassDefinitionPtr classDefinition) const;
    void DeclareClassProperty(Visibility visibility, ClassPropertyDefinitionPtr propertyDefinition) const;
    void DeclareClassMethod(Visibility visibility, ClassMethodDefinitionPtr methodDefinition) const;
    ClassDefinitionPtr GetClassDefinition(const std::string& name) const;

    ValuePtr Call(const std::string& name, const std::vector<ValuePtr>& arguments) const;

    //////////////////////////////////////////////////////
    // Current to top scope //////////////////////////////
    //////////////////////////////////////////////////////

    /**
     * @brief Assigns a value to a variable in the current scope.
     * @param name The name of the variable to assign.
     * @param value The value to assign to the variable.
     */
    void AssignVariable(const std::string& name, const ValuePtr& value) const;

    /**
     * @brief Checks if a variable is declared in any of the scopes.
     * @param name The name of the variable to check.
     * @return True if the variable is declared, false otherwise.
     */
    bool IsVariableDeclared(const std::string& name) const;

    /**
     * @brief Gets the value of a variable from the current scope.
     * @param name The name of the variable to retrieve.
     * @return The value of the variable.
     */
    ValuePtr GetVariable(const std::string& name) const;

    bool IsClassDeclared(const std::string& name) const;

    // New methods for handling return values
    void SetReturnValue(const ValuePtr& returnValue) const;
    ValuePtr GetReturnValue() const;
    bool HasReturnValue() const;
    void ResetReturnValue() const;

    void SetContinueFlag(bool flag) const;
    bool GetContinueFlag() const;

    void SetThrowFlag(bool flag) const;
    bool GetThrowFlag() const;
};
