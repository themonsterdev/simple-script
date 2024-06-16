/**
 * @file address_of_expression.hpp
 * @brief Declaration of the address of expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FAddressOfExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    FAddressOfExpression(ExpressionPtr expression);
    ValuePtr Evaluate(const FContext& context) const override;
};
