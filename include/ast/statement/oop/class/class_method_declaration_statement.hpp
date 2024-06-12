#pragma once

#include "ast/statement/interface/statement.hpp"

#include "type/oop/class_definition.hpp"
#include "type/oop/class_method_definition.hpp"

class FClassMethodDeclarationStatement final : public IStatement
{
    Visibility m_visibility;
    ClassMethodDefinitionPtr m_methodDefinition;
    StatementPtr m_body;

public:

    FClassMethodDeclarationStatement(
        Visibility visibility,
        ClassMethodDefinitionPtr methodDefinition,
        StatementPtr body
    );

    void Execute(const FContext& context) const override;

    const Visibility& GetVisibility() const;
    const StatementPtr& GetBody() const;
};