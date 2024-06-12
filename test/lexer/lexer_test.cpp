#include <gtest/gtest.h>
#include "lexer/lexer.hpp"

TEST(FLexerTest, LexerTest)
{
    const std::string& input = "var identifier = 0\n"
        "print identifier";

    FLexer lexer(input);

    auto token = lexer.GetNextToken();
    ASSERT_TRUE(token.IsSameType(eTokenType::Keyword));
    ASSERT_TRUE(token.IsSameLexeme("var"));
    ASSERT_EQ(token.GetType(), eTokenType::Keyword);
    ASSERT_EQ(token.GetLexeme(), "var");
    ASSERT_EQ(token.GetLine(), 1);
    ASSERT_EQ(token.GetColumn(), 1);

    token = lexer.GetNextToken();
    ASSERT_TRUE(token.IsSameType(eTokenType::Identifier));
    ASSERT_TRUE(token.IsSameLexeme("identifier"));
    ASSERT_EQ(token.GetType(), eTokenType::Identifier);
    ASSERT_EQ(token.GetLexeme(), "identifier");
    ASSERT_EQ(token.GetLine(), 1);
    ASSERT_EQ(token.GetColumn(), 5);

    token = lexer.GetNextToken();
    ASSERT_TRUE(token.IsSameType(eTokenType::Operator));
    ASSERT_TRUE(token.IsSameLexeme("="));
    ASSERT_EQ(token.GetType(), eTokenType::Operator);
    ASSERT_EQ(token.GetLexeme(), "=");
    ASSERT_EQ(token.GetLine(), 1);
    ASSERT_EQ(token.GetColumn(), 16);

    token = lexer.GetNextToken();
    ASSERT_TRUE(token.IsSameType(eTokenType::Number));
    ASSERT_TRUE(token.IsSameLexeme("0"));
    ASSERT_EQ(token.GetType(), eTokenType::Number);
    ASSERT_EQ(token.GetLexeme(), "0");
    ASSERT_EQ(token.GetLine(), 1);
    ASSERT_EQ(token.GetColumn(), 18);

    token = lexer.GetNextToken();
    ASSERT_TRUE(token.IsSameType(eTokenType::Keyword));
    ASSERT_TRUE(token.IsSameLexeme("print"));
    ASSERT_EQ(token.GetType(), eTokenType::Keyword);
    ASSERT_EQ(token.GetLexeme(), "print");
    ASSERT_EQ(token.GetLine(), 2);
    ASSERT_EQ(token.GetColumn(), 1);

    token = lexer.GetNextToken();
    ASSERT_TRUE(token.IsSameType(eTokenType::Identifier));
    ASSERT_TRUE(token.IsSameLexeme("identifier"));
    ASSERT_EQ(token.GetType(), eTokenType::Identifier);
    ASSERT_EQ(token.GetLexeme(), "identifier");
    ASSERT_EQ(token.GetLine(), 2);
    ASSERT_EQ(token.GetColumn(), 7);
}
