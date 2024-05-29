#include <gtest/gtest.h>            // Include Google Test framework
#include "rule/boolean_rule.hpp"    // Include the boolean rule header file

TEST(FBooleanRuleTest, MatchTrue)
{
    // Initialize test data
    std::string text = "true";
    size_t index = 0;
    SToken token;

    // Create an instance of the boolean rule
    FBooleanRule booleanRule;

    // Call the Match function of the boolean rule
    bool matchResult = booleanRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Boolean);
    ASSERT_EQ(token.lexeme, "true");
    ASSERT_EQ(index, 4); // Index should be moved to the end of "true"
}

TEST(FBooleanRuleTest, MatchFalse)
{
    // Initialize test data
    std::string text = "false";
    size_t index = 0;
    SToken token;

    // Create an instance of the boolean rule
    FBooleanRule booleanRule;

    // Call the Match function of the boolean rule
    bool matchResult = booleanRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Boolean);
    ASSERT_EQ(token.lexeme, "false");
    ASSERT_EQ(index, 5); // Index should be moved to the end of "false"
}

TEST(FBooleanRuleTest, NoMatch)
{
    // Initialize test data
    std::string text = "random";
    size_t index = 0;
    SToken token;

    // Create an instance of the boolean rule
    FBooleanRule booleanRule;

    // Call the Match function of the boolean rule
    bool matchResult = booleanRule.Match(text, index, token);

    // Verify the match result
    ASSERT_FALSE(matchResult);
    ASSERT_EQ(index, 0); // Index should remain at the initial position
}
