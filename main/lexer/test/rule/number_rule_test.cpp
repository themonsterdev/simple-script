#include "gtest/gtest.h"            // Include Google Test framework
#include "rule/number_rule.hpp"    // Include the number rule header file

TEST(FNumberRuleTest, NumberMatch)
{
    // Initialize test data
    std::string text = "12345";
    size_t index = 0;
    SToken token;

    // Create an instance of the number rule
    FNumberRule numberRule;

    // Call the Match function of the number rule
    bool matchResult = numberRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Number);
    ASSERT_EQ(token.lexeme, "12345");
    ASSERT_EQ(index, 5); // Index should be moved to the end of the number
}

TEST(FNumberRuleTest, NoMatch)
{
    // Initialize test data
    std::string text = "abc";
    size_t index = 0;
    SToken token;

    // Create an instance of the number rule
    FNumberRule numberRule;

    // Call the Match function of the number rule
    bool matchResult = numberRule.Match(text, index, token);

    // Verify the match result
    ASSERT_FALSE(matchResult);
    ASSERT_EQ(index, 0); // Index should remain at the initial position
}
