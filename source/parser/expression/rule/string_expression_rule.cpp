#include "parser/expression/rule/string_expression_rule.hpp"
#include "parser/expression/expression_parser.hpp"

bool FStringExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FStringExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
