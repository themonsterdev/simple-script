#include <gtest/gtest.h>

#include "lexer.hpp"

// lexer rules
#include "rule/comment_rule.hpp"
#include "rule/identifier_rule.hpp"
#include "rule/number_rule.hpp"
#include "rule/operator_rule.hpp"
#include "rule/string_rule.hpp"

// Test fixture for lexer
class FLexerTest : public ::testing::Test
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

// Test case for lexer
TEST_F(FLexerTest, LexerTest)
{
    std::string input;
    input += "var n = 1 + 2 * 3\n";
    input += "print n";
    FLexer lexer(input);

    TokenVector tokens = lexer.Tokenize();
    EXPECT_EQ(tokens.size(), 10);

    EXPECT_EQ(tokens[0].type, eTokenType::Keyword);
    EXPECT_EQ(tokens[0].lexeme, "var");
    EXPECT_EQ(tokens[0].line, 1);
    EXPECT_EQ(tokens[0].column, 1);

    EXPECT_EQ(tokens[1].type, eTokenType::Identifier);
    EXPECT_EQ(tokens[1].lexeme, "n");
    EXPECT_EQ(tokens[1].line, 1);
    EXPECT_EQ(tokens[1].column, 5);

    EXPECT_EQ(tokens[2].type, eTokenType::Operator);
    EXPECT_EQ(tokens[2].lexeme, "=");
    EXPECT_EQ(tokens[2].line, 1);
    EXPECT_EQ(tokens[2].column, 7);

    EXPECT_EQ(tokens[3].type, eTokenType::Number);
    EXPECT_EQ(tokens[3].lexeme, "1");
    EXPECT_EQ(tokens[3].line, 1);
    EXPECT_EQ(tokens[3].column, 9);

    EXPECT_EQ(tokens[4].type, eTokenType::Operator);
    EXPECT_EQ(tokens[4].lexeme, "+");
    EXPECT_EQ(tokens[4].line, 1);
    EXPECT_EQ(tokens[4].column, 11);

    EXPECT_EQ(tokens[5].type, eTokenType::Number);
    EXPECT_EQ(tokens[5].lexeme, "2");
    EXPECT_EQ(tokens[5].line, 1);
    EXPECT_EQ(tokens[5].column, 13);

    EXPECT_EQ(tokens[6].type, eTokenType::Operator);
    EXPECT_EQ(tokens[6].lexeme, "*");
    EXPECT_EQ(tokens[6].line, 1);
    EXPECT_EQ(tokens[6].column, 15);

    EXPECT_EQ(tokens[7].type, eTokenType::Number);
    EXPECT_EQ(tokens[7].lexeme, "3");
    EXPECT_EQ(tokens[7].line, 1);
    EXPECT_EQ(tokens[7].column, 17);

    EXPECT_EQ(tokens[8].type, eTokenType::Keyword);
    EXPECT_EQ(tokens[8].lexeme, "print");
    EXPECT_EQ(tokens[8].line, 2);
    EXPECT_EQ(tokens[8].column, 1);

    EXPECT_EQ(tokens[9].type, eTokenType::Identifier);
    EXPECT_EQ(tokens[9].lexeme, "n");
    EXPECT_EQ(tokens[9].line, 2);
    EXPECT_EQ(tokens[9].column, 7);
}

// Test case for lexer with declaration list
TEST_F(FLexerTest, LexerDeclarationListTest)
{
    std::string input("var x, y = 1, z = 2");
    FLexer lexer(input);

    TokenVector tokens = lexer.Tokenize();
    EXPECT_EQ(tokens.size(), 10);

    EXPECT_EQ(tokens[0].type, eTokenType::Keyword);
    EXPECT_EQ(tokens[0].lexeme, "var");
    EXPECT_EQ(tokens[0].line, 1);
    EXPECT_EQ(tokens[0].column, 1);

    EXPECT_EQ(tokens[1].type, eTokenType::Identifier);
    EXPECT_EQ(tokens[1].lexeme, "x");

    EXPECT_EQ(tokens[2].type, eTokenType::Punctuation);
    EXPECT_EQ(tokens[2].lexeme, ",");

    EXPECT_EQ(tokens[3].type, eTokenType::Identifier);
    EXPECT_EQ(tokens[3].lexeme, "y");

    EXPECT_EQ(tokens[4].type, eTokenType::Operator);
    EXPECT_EQ(tokens[4].lexeme, "=");

    EXPECT_EQ(tokens[5].type, eTokenType::Number);
    EXPECT_EQ(tokens[5].lexeme, "1");

    EXPECT_EQ(tokens[6].type, eTokenType::Punctuation);
    EXPECT_EQ(tokens[6].lexeme, ",");

    EXPECT_EQ(tokens[7].type, eTokenType::Identifier);
    EXPECT_EQ(tokens[7].lexeme, "z");

    EXPECT_EQ(tokens[8].type, eTokenType::Operator);
    EXPECT_EQ(tokens[8].lexeme, "=");

    EXPECT_EQ(tokens[9].type, eTokenType::Number);
    EXPECT_EQ(tokens[9].lexeme, "2");
}
