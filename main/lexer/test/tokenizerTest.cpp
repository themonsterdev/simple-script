#include <gtest/gtest.h>
#include "tokenizer.hpp"

// Test fixture pour les expressions
class TokenizerTest : public ::testing::Test
{
protected:

    // Fonction SetUp() sera appelée avant chaque test
    void SetUp() override
    {
        // Initialisation des ressources communes pour les tests
    }

    // Fonction TearDown() sera appelée après chaque test
    void TearDown() override
    {
        // Nettoyage des ressources communes après les tests
    }
};

TEST_F(TokenizerTest, TokenizeNumberTest)
{
    const std::vector<std::string> keywords = {};
    FTokenizer tokenizer("123456789", keywords);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::NUMBER);
    EXPECT_EQ(token.lexeme, "123456789");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeStringSingleQuoteTest)
{
    const std::vector<std::string> keywords = {};
    FTokenizer tokenizer("'Hello, world'", keywords);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::STRING);
    EXPECT_EQ(token.lexeme, "Hello, world");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeStringDoubleQuoteTest)
{
    const std::vector<std::string> keywords = {};
    FTokenizer tokenizer("\"Hello, world\"", keywords);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::STRING);
    EXPECT_EQ(token.lexeme, "Hello, world");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeStringBacktickQuoteTest)
{
    const std::vector<std::string> keywords = {};
    FTokenizer tokenizer("`Hello, world`", keywords);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::STRING);
    EXPECT_EQ(token.lexeme, "Hello, world");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeVarNumberTest)
{
    const std::vector<std::string> keywords = { "var" };
    FTokenizer tokenizer("var n = 0", keywords);
    
    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::KEYWORD);
    EXPECT_EQ(token.lexeme, "var");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::IDENTIFIER);
    EXPECT_EQ(token.lexeme, "n");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::OPERATOR);
    EXPECT_EQ(token.lexeme, "=");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::NUMBER);
    EXPECT_EQ(token.lexeme, "0");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeVarNumberPrintTest)
{
    const std::vector<std::string> keywords = { "var", "print" };
    FTokenizer tokenizer("var n = 0\nprint n", keywords);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::KEYWORD);
    EXPECT_EQ(token.lexeme, "var");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::IDENTIFIER);
    EXPECT_EQ(token.lexeme, "n");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::OPERATOR);
    EXPECT_EQ(token.lexeme, "=");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::NUMBER);
    EXPECT_EQ(token.lexeme, "0");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::KEYWORD);
    EXPECT_EQ(token.lexeme, "print");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::IDENTIFIER);
    EXPECT_EQ(token.lexeme, "n");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeVarStringTest)
{
    const std::vector<std::string> keywords = { "var" };
    FTokenizer tokenizer("var n = \"Hello, world\"", keywords);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::KEYWORD);
    EXPECT_EQ(token.lexeme, "var");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::IDENTIFIER);
    EXPECT_EQ(token.lexeme, "n");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::OPERATOR);
    EXPECT_EQ(token.lexeme, "=");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::STRING);
    EXPECT_EQ(token.lexeme, "Hello, world");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeCommentTest)
{
    const std::vector<std::string> keywords = {};

    const std::vector<SComment> comments = {
        { eCommentType::SINGLE_LINE, "//", "\n", false },
        { eCommentType::MULTI_LINE,  "/*", "*/", false },
        { eCommentType::MULTI_LINE,  "{%", "%}", false },
    };

    std::string input;
    input += "// comment single line\n";
    input += "/* comment multi line */\n";
    input += "{% comment multi line %}";

    FTokenizer tokenizer(input, keywords, comments);

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::COMMENT);
    EXPECT_EQ(token.lexeme, "// comment single line");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::COMMENT);
    EXPECT_EQ(token.lexeme, "/* comment multi line */");

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::COMMENT);
    EXPECT_EQ(token.lexeme, "{% comment multi line %}");

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}

TEST_F(TokenizerTest, TokenizeSkipCommentTest)
{
    const std::vector<std::string> keywords = {};

    const std::vector<SComment> comments = {
        { eCommentType::SINGLE_LINE, "//", "\n", true },
        { eCommentType::MULTI_LINE,  "/*", "*/", true },
        { eCommentType::MULTI_LINE,  "{%", "%}", true },
    };

    std::string input;
    input += "// comment single line\n";
    input += "/* comment multi line */\n";
    input += "{% comment multi line %}";

    FTokenizer tokenizer(input, keywords, comments);

    EXPECT_EQ(tokenizer.HasNextToken(), false);
    SToken token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}
