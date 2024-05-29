#include "gtest/gtest.h"                    // Include Google Test framework
#include "rule/punctuation_rule.hpp"       // Include the punctuation rule header file

TEST(FPunctuationRuleTest, PunctuationMatch)
{
    // Initialize test data
    std::string text = ",";
    size_t index = 0;
    SToken token;

    // Create an instance of the punctuation rule
    FPunctuationRule punctuationRule;

    // Call the Match function of the punctuation rule
    bool matchResult = punctuationRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Punctuation);
    ASSERT_EQ(token.lexeme, ",");
    ASSERT_EQ(index, 1); // Index should be moved to the end of the punctuation
}

TEST(FPunctuationRuleTest, NoMatch)
{
    // Initialize test data
    std::string text = "123";
    size_t index = 0;
    SToken token;

    // Create an instance of the punctuation rule
    FPunctuationRule punctuationRule;

    // Call the Match function of the punctuation rule
    bool matchResult = punctuationRule.Match(text, index, token);

    // Verify the match result
    ASSERT_FALSE(matchResult);
    ASSERT_EQ(index, 0); // Index should remain at the initial position
}
