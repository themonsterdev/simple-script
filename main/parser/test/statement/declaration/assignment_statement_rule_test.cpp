#include <gtest/gtest.h>

#include "lexer.hpp"

#include "expression/expression_parser.hpp"
#include "expression/operator/additive/addition_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/identifier_expression.hpp"

#include "statement/statement_parser.hpp"
#include "statement/declaration/assignment_statement.hpp"

TEST(FParserAssignmentStatementTest, ParseSimpleAssignmentStatement)
{
    std::string input("x = 10");
    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& assignmentStatement = dynamic_cast<FAssignmentStatement*>(statement.get());
    ASSERT_NE(assignmentStatement, nullptr);
    EXPECT_EQ(assignmentStatement->GetIdentifier(), "x");

    const auto& expression = assignmentStatement->GetExpression();
    ASSERT_NE(expression, nullptr);

    const auto& numberExpression = dynamic_cast<FNumberExpression*>(expression.get());
    ASSERT_NE(numberExpression, nullptr);
    EXPECT_EQ(numberExpression->GetValue(), 10);
}

TEST(FParserAssignmentStatementTest, ParseAssignmentStatementWithComplexIdentifier)
{
    std::string input("my_variable = another_variable + 5");
    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& varStatement = dynamic_cast<FAssignmentStatement*>(statement.get());
    ASSERT_NE(varStatement, nullptr);
    EXPECT_EQ(varStatement->GetIdentifier(), "my_variable");

    const auto& expression = varStatement->GetExpression();
    ASSERT_NE(expression, nullptr);

    const auto& addExpression = dynamic_cast<FAdditionExpression*>(expression.get());
    ASSERT_NE(addExpression, nullptr);

    const auto& leftExpression = addExpression->GetLeft();
    ASSERT_NE(leftExpression, nullptr);

    const auto& leftIdExpression = dynamic_cast<FIdentifierExpression*>(leftExpression.get());
    ASSERT_NE(leftIdExpression, nullptr);
    EXPECT_EQ(leftIdExpression->GetName(), "another_variable");

    const auto& rightExpression = addExpression->GetRight();
    ASSERT_NE(rightExpression, nullptr);

    const auto& rightIdExpression = dynamic_cast<FNumberExpression*>(rightExpression.get());
    ASSERT_NE(rightIdExpression, nullptr);
    EXPECT_EQ(rightIdExpression->GetValue(), 5);
}
