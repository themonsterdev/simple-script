#pragma once

#include "expression/interface/expression_rule.hpp"

class FNumberExpressionRule : public IExpressionRule
{
public:

	bool Match(FExpressionParser& parser) const override;

	ExpressionPtr Parse(FExpressionParser& parser) const override;
};
