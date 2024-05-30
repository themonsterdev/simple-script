#include "expression/rule/identifier_expression_rule.hpp"
#include "expression/expression_parser.hpp"

bool FIdentifierExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FIdentifierExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
