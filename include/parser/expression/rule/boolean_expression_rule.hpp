#pragma once

#include "parser/expression/interface/expression_rule.hpp"

class FBooleanExpressionRule : public IExpressionRule
{
public:

	bool Match(FExpressionParser& parser) const override;

	ExpressionPtr Parse(FExpressionParser& parser) const override;
};
