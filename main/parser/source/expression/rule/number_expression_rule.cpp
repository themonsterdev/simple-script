#include "expression/rule/number_expression_rule.hpp"
#include "expression/expression_parser.hpp"

bool FNumberExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FNumberExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
