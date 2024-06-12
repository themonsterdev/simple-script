#include "parser/expression/rule/boolean_expression_rule.hpp"
#include "parser/expression/expression_parser.hpp"

bool FBooleanExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FBooleanExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
