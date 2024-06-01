#include <gtest/gtest.h>

#include "lexer.hpp"
#include "context.hpp"

#include "expression/expression_parser.hpp"
#include "expression/string_operator_expression.hpp"

// Test fixture for expressions
class FParserStringOperatorExpressionTest : public ::testing::Test
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

// TEST_F(FParserStringOperatorExpressionTest, ParseSimpleStringRepeat)
// {
//     std::string input("2 * \"a\"");
//     FLexer lexer(input);
// 
//     // 2
//     auto token = lexer.PeekNextToken(0);
//     EXPECT_EQ(token.type, eTokenType::Number);
//     EXPECT_EQ(token.lexeme, "2");
// 
//     // *
//     token = lexer.PeekNextToken(1);
//     EXPECT_EQ(token.type, eTokenType::Operator);
//     EXPECT_EQ(token.lexeme, "*");
// 
//     // "a" -> token is ignoring quotes
//     token = lexer.PeekNextToken(2);
//     EXPECT_EQ(token.type, eTokenType::String);
//     EXPECT_EQ(token.lexeme, "a");
// 
//     FExpressionParser parser(lexer);
// 
//     auto expression = parser.ParseExpression();
//     ASSERT_NE(expression, nullptr);
// 
//     auto stringRepeatExpression = dynamic_cast<FStringOperatorExpression*>(expression.get());
//     ASSERT_NE(stringRepeatExpression, nullptr);
// 
//     Value value = stringRepeatExpression->Evaluate(context);
//     EXPECT_EQ(value, Value("aa"));
// }

// TEST_F(FParserStringOperatorExpressionTest, ParseSimpleStringConcat)
// {
//     std::string input("\"hello\" + \", \" + \"world\"");
//     FLexer lexer(input);
// 
//     auto token = lexer.PeekNextToken();
//     EXPECT_EQ(token.type, eTokenType::String);
//     EXPECT_EQ(token.lexeme, "hello");
// 
//     FExpressionParser parser(lexer);
// 
//     auto expression = parser.ParseExpression();
//     ASSERT_NE(expression, nullptr);
// 
//     auto stringRepeatExpression = dynamic_cast<FStringOperatorExpression*>(expression.get());
//     ASSERT_NE(stringRepeatExpression, nullptr);
// 
//     Value value = stringRepeatExpression->Evaluate(context);
//     EXPECT_EQ(value, Value("hello, world"));
// }
