#include <gtest/gtest.h>

// lexer rules
#include "rule/comment_rule.hpp"
#include "rule/identifier_rule.hpp"
#include "rule/number_rule.hpp"
#include "rule/operator_rule.hpp"
#include "rule/string_rule.hpp"

// Test fixture for lexer rules
class LexerRulesTest : public ::testing::Test
{
protected:

    // SetUp function will be called before each test
    void SetUp() override
    {
        // Initialize common resources for tests
    }

    // TearDown function will be called after each test
    void TearDown() override
    {
        // Clean up common resources after tests
    }
};

// Test case for identifier rule
TEST_F(LexerRulesTest, IdentifierRule)
{
    FIdentifierRule rule;
    SToken token;
    size_t index = 0;
    std::string input = "myVariable123";

    ASSERT_TRUE(rule.Match(input, index, token));
    EXPECT_EQ(token.type, eTokenType::Identifier);
    EXPECT_EQ(token.lexeme, "myVariable123");
    EXPECT_EQ(index, 13);
}

// Test case for number rule
TEST_F(LexerRulesTest, NumberRule)
{
    FNumberRule rule;
    SToken token;
    size_t index = 0;
    std::string input = "12345";

    ASSERT_TRUE(rule.Match(input, index, token));
    EXPECT_EQ(token.type, eTokenType::Number);
    EXPECT_EQ(token.lexeme, "12345");
    EXPECT_EQ(index, 5);
}

// Test case for string rule
TEST_F(LexerRulesTest, StringRule)
{
    FStringRule rule;
    SToken token;
    size_t index = 0;
    std::string input = "\"Hello, World!\"";

    ASSERT_TRUE(rule.Match(input, index, token));
    EXPECT_EQ(token.type, eTokenType::String);
    EXPECT_EQ(token.lexeme, "Hello, World!");
    EXPECT_EQ(index, 15);
}

// Test case for operator rule
TEST_F(LexerRulesTest, OperatorRule)
{
    FOperatorRule rule;
    SToken token;
    size_t index = 0;
    std::string input = "+";

    ASSERT_TRUE(rule.Match(input, index, token));
    EXPECT_EQ(token.type, eTokenType::Operator);
    EXPECT_EQ(token.lexeme, "+");
    EXPECT_EQ(index, 1);
}

// Test case for single-line comment rule
TEST_F(LexerRulesTest, CommentSingleLineRule)
{
    FCommentRule rule;
    SToken token;
    size_t index = 0;
    std::string input = "// This is a comment\n";

    ASSERT_TRUE(rule.Match(input, index, token));
    EXPECT_EQ(token.type, eTokenType::Comment);
    EXPECT_EQ(token.lexeme, "// This is a comment");
    EXPECT_EQ(index, 20);
}

// Test case for multi-line comment rule
TEST_F(LexerRulesTest, CommentMultiLineRule)
{
    FCommentRule rule;
    SToken token;
    size_t index = 0;
    std::string input = "/**\n";
    input += " * One line\n";
    input += " * Two line\n";
    input += " * three line\n";
    input += " * four line\n";
    input += " */";

    ASSERT_TRUE(rule.Match(input, index, token));
    EXPECT_EQ(token.type, eTokenType::Comment);
    EXPECT_EQ(token.lexeme, input);
    EXPECT_EQ(index, 58);
}
