#include "parser/expression/rule/string_operator_expression_rule.hpp"
#include "parser/expression/expression_parser.hpp"

bool FStringOperatorExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FStringOperatorExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
