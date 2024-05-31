#include <gtest/gtest.h>

// Base includes
#include "lexer.hpp"

// Expression includes
#include "expression/expression_parser.hpp"
#include "expression/literal/boolean_expression.hpp"
#include "expression/identifier_expression.hpp"

class FParserBooleanExpressionTest : public ::testing::Test
{
protected:

    void SetUp() override
    {
        // Initialisation du lexer avec le texte source vide
    }
};

TEST_F(FParserBooleanExpressionTest, ParseTrueBoolean)
{
    std::string source("true");
    FLexer lexer(source);

    const auto& token = lexer.PeekNextToken();
    ASSERT_EQ(token.type, eTokenType::Boolean);
    ASSERT_EQ(token.lexeme, "true");

    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto booleanExpression = dynamic_cast<FBooleanExpression*>(expression.get());
    ASSERT_NE(booleanExpression, nullptr);

    EXPECT_TRUE(booleanExpression->GetValue());
}

TEST_F(FParserBooleanExpressionTest, ParseFalseBoolean)
{
    std::string source("false");
    FLexer lexer(source);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto booleanExpression = dynamic_cast<FBooleanExpression*>(expression.get());
    ASSERT_NE(booleanExpression, nullptr);

    EXPECT_FALSE(booleanExpression->GetValue());
}

// TEST_F(FParserBooleanExpressionTest, ParseComplexBooleanExpression)
// {
//     std::string source("true || false && true");
// 
//     FLexer lexer(source);
//     FExpressionParser parser(lexer);
// 
//     auto expression = parser.ParseExpression();
//     ASSERT_NE(expression, nullptr);
// 
//     // Ajoutez des assertions supplémentaires ici pour vérifier la structure interne de l'expression
// }
