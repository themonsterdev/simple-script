#include "parser/expression/rule/identifier_expression_rule.hpp"
#include "parser/expression/expression_parser.hpp"

bool FIdentifierExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FIdentifierExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
