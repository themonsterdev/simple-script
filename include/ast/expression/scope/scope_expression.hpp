/**
 * @file scope_expression.hpp
 * @brief Declaration of the scope expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"
#include <string>

class FScopeExpression final : public IExpression
{
    ExpressionPtr m_left;
    std::string m_right; // member name or scope

public:

    FScopeExpression(ExpressionPtr left, std::string right);
    ValuePtr Evaluate(const FContext& context) const override;
};
