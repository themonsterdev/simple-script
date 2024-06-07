#pragma once

#include "expression/interface/expression.hpp"
#include <string>

class FPropertyDeclarationStatement final : public IStatement
{
    std::string m_visibility;
    std::string m_name;
    ExpressionPtr m_expression;

public:

    FPropertyDeclarationStatement(
        std::string visibility,
        std::string name,
        ExpressionPtr expression
    );

    void Execute(const FContext& context) const override;

    const std::string& GetVisibility() const;
    const std::string& GetName() const;
    const ExpressionPtr& GetExpression() const;
};
