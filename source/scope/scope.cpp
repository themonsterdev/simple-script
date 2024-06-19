/**
 * @file scope.cpp
 * @brief Implementation of the FScope class.
 */

#include "scope/scope.hpp"  // Include for the FScope class declaration
#include <stdexcept>        // Include for std::runtime_error

void FScope::AddSymbol(const std::string& name, const ValuePtr& value)
{
    if (IsSymbolDeclared(name))
    {
        throw std::runtime_error("Symbol already declared: " + name);
    }

    m_symbols[name] = value;
}

bool FScope::IsSymbolDeclared(const std::string& name) const
{
    return m_symbols.find(name) != m_symbols.end();
}

ValuePtr FScope::GetSymbol(const std::string& name) const
{
    // Check if the symbol exists in the scope
    auto it = m_symbols.find(name);
    if (it != m_symbols.end())
    {
        // Return the value of the symbol if found
        return it->second;
    }

    // Throw an exception if the symbol is not found
    throw std::runtime_error("Undefined symbol: " + name);
}

void FScope::DeclareSymbol(const std::string& name)
{
    if (IsSymbolDeclared(name))
    {
        throw std::runtime_error("Symbol already declared: " + name);
    }

    // Default initialization
    m_symbols[name] = nullptr;
}

void FScope::AssignSymbol(const std::string& name, const ValuePtr& value)
{
    if (!IsSymbolDeclared(name))
    {
        throw std::runtime_error("Symbol not declared: " + name);
    }

    m_symbols[name] = value;
}
