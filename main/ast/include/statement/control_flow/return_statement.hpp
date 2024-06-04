/**
 * @file return_statement.hpp
 * @brief Declaration of the return statement class.
 */

#pragma once

#include "statement/interface/statement.hpp"
#include "expression/interface/expression.hpp"

class FReturnStatement final : public IStatement
{
    ExpressionPtr m_returnValue;

public:

    explicit FReturnStatement(ExpressionPtr returnValue);

    void Execute(const FContext& context) const override;

    const ExpressionPtr& GetReturnValue() const;
};
