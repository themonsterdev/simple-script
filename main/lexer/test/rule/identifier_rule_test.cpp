#include "gtest/gtest.h"                // Include Google Test framework
#include "rule/identifier_rule.hpp"    // Include the identifier rule header file

TEST(FIdentifierRuleTest, IdentifierMatch)
{
    // Initialize test data
    std::string text = "variable123";
    size_t index = 0;
    SToken token;

    // Create an instance of the identifier rule
    FIdentifierRule identifierRule;

    // Call the Match function of the identifier rule
    bool matchResult = identifierRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Identifier);
    ASSERT_EQ(token.lexeme, "variable123");
    ASSERT_EQ(index, 11); // Index should be moved to the end of the identifier
}

TEST(FIdentifierRuleTest, KeywordMatch)
{
    // Initialize test data
    std::string text = "var";
    size_t index = 0;
    SToken token;

    // Create an instance of the identifier rule
    FIdentifierRule identifierRule;

    // Call the Match function of the identifier rule
    bool matchResult = identifierRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Keyword);
    ASSERT_EQ(token.lexeme, "var");
    ASSERT_EQ(index, 3); // Index should be moved to the end of the keyword
}

TEST(FIdentifierRuleTest, NoIdentifierMatch)
{
    // Initialize test data
    std::string text = "123variable";
    size_t index = 0;
    SToken token;

    // Create an instance of the identifier rule
    FIdentifierRule identifierRule;

    // Call the Match function of the identifier rule
    bool matchResult = identifierRule.Match(text, index, token);

    // Verify the match result
    ASSERT_FALSE(matchResult);
    ASSERT_EQ(index, 0); // Index should remain at the initial position
}
