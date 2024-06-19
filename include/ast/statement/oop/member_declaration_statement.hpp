#pragma once

#include "ast/statement/interface/statement.hpp"
#include "type/oop/class_definition.hpp"

class FMemberDeclarationStatement final : public IStatement
{
    Visibility m_visibility;
    StatementPtr m_statement;

public:

    FMemberDeclarationStatement(
        Visibility visibility,
        StatementPtr statement
    );

    void Execute(const FContext& context) const override;

    Visibility GetVisibility() const;
    const StatementPtr& GetStatement() const;
};
