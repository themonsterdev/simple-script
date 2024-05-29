#include "gtest/gtest.h"                // Include Google Test framework
#include "rule/operator_rule.hpp"      // Include the operator rule header file

TEST(FOperatorRuleTest, OperatorMatch)
{
    // Initialize test data
    std::string text = "+";
    size_t index = 0;
    SToken token;

    // Create an instance of the operator rule
    FOperatorRule operatorRule;

    // Call the Match function of the operator rule
    bool matchResult = operatorRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Operator);
    ASSERT_EQ(token.lexeme, "+");
    ASSERT_EQ(index, 1); // Index should be moved to the end of the operator
}

TEST(FOperatorRuleTest, NoMatch)
{
    // Initialize test data
    std::string text = "123";
    size_t index = 0;
    SToken token;

    // Create an instance of the operator rule
    FOperatorRule operatorRule;

    // Call the Match function of the operator rule
    bool matchResult = operatorRule.Match(text, index, token);

    // Verify the match result
    ASSERT_FALSE(matchResult);
    ASSERT_EQ(index, 0); // Index should remain at the initial position
}
