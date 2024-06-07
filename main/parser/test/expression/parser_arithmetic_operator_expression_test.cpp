#include <gtest/gtest.h>

// Base includes
#include "lexer.hpp"
#include "context.hpp"
#include "parser.hpp"

// Expression includes
#include "expression/operator/additive/addition_expression.hpp"
#include "expression/operator/additive/subtraction_expression.hpp"
#include "expression/operator/multiplicative/multiply_expression.hpp"
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Test fixture for expressions
class FParserArithmeticOperatorExpressionTest : public ::testing::Test
{
protected:

    FContext context;

    // SetUp() function will be called before each test
    void SetUp() override
    {
        // Initialize the context with necessary variables for the tests
    }

    // TearDown() function will be called after each test
    void TearDown() override
    {
        // Clean up after tests if necessary
    }
};

// Test for a simple addition expression
// TEST_F(FParserArithmeticOperatorExpressionTest, ParseSimpleAddition)
// {
//     std::string input = "1 + 2";
//     FLexer lexer(input);
//     FExpressionParser parser(lexer);
// 
//     const auto& expression = parser.ParseExpression();
//     ASSERT_NE(expression, nullptr);
// 
//     const auto& addExpr = dynamic_cast<FAdditionExpression*>(expression.get());
//     ASSERT_NE(addExpr, nullptr);
// 
//     auto leftExpr = dynamic_cast<FNumberExpression*>(addExpr->GetLeft().get());
//     auto rightExpr = dynamic_cast<FNumberExpression*>(addExpr->GetRight().get());
//     ASSERT_NE(leftExpr, nullptr);
//     ASSERT_NE(rightExpr, nullptr);
// 
//     EXPECT_EQ(leftExpr->Evaluate(context), Value(1));
//     EXPECT_EQ(rightExpr->Evaluate(context), Value(2));
// }

// Test for a simple subtract expression
TEST_F(FParserArithmeticOperatorExpressionTest, ParseSimpleSubtract)
{
    std::string input = "2 - 2";
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    const auto& expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    const auto& addExpr = dynamic_cast<FSubtractionExpression*>(expression.get());
    ASSERT_NE(addExpr, nullptr);

    auto leftExpr = dynamic_cast<FNumberExpression*>(addExpr->GetLeft().get());
    auto rightExpr = dynamic_cast<FNumberExpression*>(addExpr->GetRight().get());
    ASSERT_NE(leftExpr, nullptr);
    ASSERT_NE(rightExpr, nullptr);

    // EXPECT_EQ(leftExpr->Evaluate(context), Value(2));
    // EXPECT_EQ(rightExpr->Evaluate(context), Value(2));
}

// Test for a simple multiply expression
TEST_F(FParserArithmeticOperatorExpressionTest, ParseSimpleMultiply)
{
    std::string input = "2 * 2";
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    const auto& expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    const auto& addExpr = dynamic_cast<FMultiplicationExpression*>(expression.get());
    ASSERT_NE(addExpr, nullptr);

    auto leftExpr = dynamic_cast<FNumberExpression*>(addExpr->GetLeft().get());
    auto rightExpr = dynamic_cast<FNumberExpression*>(addExpr->GetRight().get());
    ASSERT_NE(leftExpr, nullptr);
    ASSERT_NE(rightExpr, nullptr);

    // EXPECT_EQ(leftExpr->Evaluate(context), Value(2));
    // EXPECT_EQ(rightExpr->Evaluate(context), Value(2));
}

// Test for a nested addition and multiplication expression
TEST_F(FParserArithmeticOperatorExpressionTest, ParseNestedAdditionMultiplication)
{
    std::string input = "1 + 2 * 3";
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    const auto& expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto addExpr = dynamic_cast<FAdditionExpression*>(expression.get());
    ASSERT_NE(addExpr, nullptr);

    auto leftExpr = dynamic_cast<FNumberExpression*>(addExpr->GetLeft().get());
    auto rightExpr = dynamic_cast<FMultiplicationExpression*>(addExpr->GetRight().get());
    ASSERT_NE(leftExpr, nullptr);
    ASSERT_NE(rightExpr, nullptr);

    // EXPECT_EQ(leftExpr->Evaluate(context), Value(1));

    // auto rightLeftExpr = dynamic_cast<FNumberExpression*>(rightExpr->GetLeft().get());
    // auto rightRightExpr = dynamic_cast<FNumberExpression*>(rightExpr->GetRight().get());
    // ASSERT_NE(rightLeftExpr, nullptr);
    // ASSERT_NE(rightRightExpr, nullptr);
    // 
    // EXPECT_EQ(rightLeftExpr->Evaluate(context), Value(2));
    // EXPECT_EQ(rightRightExpr->Evaluate(context), Value(3));
}

// Test for an invalid expression
TEST_F(FParserArithmeticOperatorExpressionTest, ParseInvalidExpression)
{
    std::string input = "1 + ";
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    EXPECT_THROW({
        const auto& expression = parser.ParseExpression();
        }, std::runtime_error);
}

// Test for a variable assignment with an arithmetic expression
TEST_F(FParserArithmeticOperatorExpressionTest, ParseVariableAssignment)
{
    std::string input = "var result = 1 + 2 * 3";
    FLexer lexer(input);
    FParser parser(lexer);

    StatementList statements = parser.Parse();
    ASSERT_EQ(statements.size(), 1);

    // Execute the statements to set the variables in context
    // for (const auto& stmt : statements)
    // {
    //     stmt->Execute(context);
    // }
    // 
    // auto resultVar = context.GetVariable("result");
    // EXPECT_EQ(resultVar, Value(7));  // 1 + 2 * 3
}

// Test for arithmetic operations with variables
TEST_F(FParserArithmeticOperatorExpressionTest, ParseArithmeticWithVariables)
{
    std::string input = "var a = 5\nvar b = 10\nvar result = a + b * 2";
    FLexer lexer(input);
    FParser parser(lexer);

    StatementList statements = parser.Parse();
    ASSERT_EQ(statements.size(), 3);

    // Execute the statements to set the variables in context
    // for (const auto& stmt : statements)
    // {
    //     stmt->Execute(context);
    // }
    // 
    // auto resultVar = context.GetVariable("result");
    // 
    // EXPECT_EQ(resultVar, Value(25));  // 5 + 10 * 2
}
