#include "parser/expression/rule/arithmetic_operator_expression_rule.hpp"
#include "parser/expression/expression_parser.hpp"

bool FArithmeticOperatorExpressionRule::Match(FExpressionParser& parser) const
{
    return false;
}

ExpressionPtr FArithmeticOperatorExpressionRule::Parse(FExpressionParser& parser) const
{
    return nullptr;
}
