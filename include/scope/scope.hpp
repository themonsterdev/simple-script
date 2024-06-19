/**
 * @file scope.hpp
 * @brief Declaration of the FScope class.
 */

// Ensure this file is included only once
#pragma once

#include <unordered_map>    // Include for std::unordered_map
#include <string>           // Include for std::string
#include <vector>           // Include for std::vector
#include <memory>           // Include for memory
#include <deque>            // Include for deque

#include "value/interface/value.hpp"

using SymbolMap = std::unordered_map<std::string, ValuePtr>;

/**
 * @brief Represents a scope for storing variables and their values.
 *
 * This class manages variables within a scope and provides methods to add, retrieve, and remove variables.
 */
class FScope final
{
    SymbolMap m_symbols;
    std::string m_lastClass;

public:

    void AddSymbol(const std::string& name, const ValuePtr& value);
    bool IsSymbolDeclared(const std::string& name) const;
    ValuePtr GetSymbol(const std::string& name) const;
    void DeclareSymbol(const std::string& name);
    void AssignSymbol(const std::string& name, const ValuePtr& value);
};

using ScopePtr   = std::shared_ptr<FScope>;
using ScopeDeque = std::deque<ScopePtr>;
