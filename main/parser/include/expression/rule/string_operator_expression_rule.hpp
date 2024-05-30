#pragma once

#include "expression/interface/expression_rule.hpp"

class FStringOperatorExpressionRule : public IExpressionRule
{
public:

	bool Match(FExpressionParser& parser) const override;

	ExpressionPtr Parse(FExpressionParser& parser) const override;
};
