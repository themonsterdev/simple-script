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
    mutable ScopeDeque m_scopes;
    mutable ValuePtr m_returnValue;
    mutable bool m_hasReturnValue;
    mutable bool m_continueFlag;
    mutable bool m_throwFlag;

    mutable ValuePtr m_currentClass;
    mutable bool m_hasCurrentClass;

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

    void AddSymbol(const std::string& name, const ValuePtr& value) const;
    bool IsSymbolDeclared(const std::string& name) const;
    ValuePtr GetSymbol(const std::string& name) const;
    void DeclareSymbol(const std::string& name) const;
    void AssignSymbol(const std::string& name, const ValuePtr& value) const;
    
    ValuePtr Call(const std::string& name, const std::vector<ValuePtr>& arguments) const;

    // New methods for handling return values
    void SetReturnValue(const ValuePtr& returnValue) const;
    ValuePtr GetReturnValue() const;
    bool HasReturnValue() const;
    void ResetReturnValue() const;

    void SetContinueFlag(bool flag) const;
    bool GetContinueFlag() const;

    void SetThrowFlag(bool flag) const;
    bool GetThrowFlag() const;

    void SetCurrentClass(const ValuePtr& returnValue) const;
    ValuePtr GetCurrentClass() const;
    bool HasCurrentClass() const;
    void ResetCurrentClass() const;
};
