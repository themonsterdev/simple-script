/**
 * @file interface_declaration_statement.hpp
 * @brief Declaration of the interface statement class.
 */

// Ensure this file is included only once
#pragma once

// Include the interface for language statements
#include "statement/interface/statement.hpp"
#include <string>

class FInterfaceDeclarationStatement final : public IStatement
{
    std::string m_interfaceName;
    StatementList m_interfaceMethods;

public:

    FInterfaceDeclarationStatement(
        const std::string& interfaceName,
        StatementList interfaceMethods
    );

    void Execute(const FContext& context) const override;

    std::string GetInterfaceName() const;
    const StatementList& GetInterfaceMethods() const;
};
