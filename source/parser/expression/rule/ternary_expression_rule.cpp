#include "parser/expression/rule/ternary_expression_rule.hpp"
#include "parser/expression/expression_parser.hpp"

bool FTernaryExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FTernaryExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
