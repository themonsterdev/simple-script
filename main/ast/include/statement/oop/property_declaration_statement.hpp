#pragma once

#include "expression/interface/expression.hpp"
#include "oop/class_property_definition.hpp"

class FPropertyDeclarationStatement final : public IStatement
{
    Visibility m_visibility;
    ClassPropertyDefinitionPtr m_propertyDefinition;
    ExpressionPtr m_expression;

public:

    FPropertyDeclarationStatement(
        Visibility visibility,
        ClassPropertyDefinitionPtr propertyDefinition,
        ExpressionPtr expression
    );

    void Execute(const FContext& context) const override;

    Visibility GetVisibility() const;
    ClassPropertyDefinitionPtr GetPropertyDefinition() const;
    const ExpressionPtr& GetExpression() const;
};
