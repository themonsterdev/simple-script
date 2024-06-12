/**
 * @file enum_declaration_statement.hpp
 * @brief Declaration of the enum declaration statement class.
 */

// Ensure this file is included only once
#pragma once

#include "ast/statement/interface/statement.hpp"
#include "ast/expression/interface/expression.hpp"
#include "type/enum/enum_definition.hpp"

class FEnumDeclarationStatement final : public IStatement
{
    EnumDefinitionPtr m_enumDefinition;
    ExpressionList m_expressions;

public:

    FEnumDeclarationStatement(
        EnumDefinitionPtr enumDefinition,
        ExpressionList expressions
    );

    void Execute(const FContext& context) const override;
};
