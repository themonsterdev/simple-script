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

TEST_F(TokenizerTest, TokenizeTest)
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

    EXPECT_EQ(tokenizer.HasNextToken(), true);
    token = tokenizer.GetNextToken();
    EXPECT_EQ(token.type, eTokenType::END);
    EXPECT_EQ(token.lexeme, "");
}
