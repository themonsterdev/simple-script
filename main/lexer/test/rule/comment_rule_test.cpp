#include "gtest/gtest.h"                // Include Google Test framework
#include "rule/comment_rule.hpp"        // Include the comment rule header file

TEST(FCommentRuleTest, SingleLineCommentMatch)
{
    // Initialize test data
    std::string text = "// This is a single-line comment";
    size_t index = 0;
    SToken token;

    // Create an instance of the comment rule
    FCommentRule commentRule;

    // Call the Match function of the comment rule
    bool matchResult = commentRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Comment);
    ASSERT_EQ(token.lexeme, "// This is a single-line comment");
    ASSERT_EQ(index, 32); // Index should be moved to the end of the comment
}

TEST(FCommentRuleTest, MultiLineCommentMatch)
{
    // Initialize test data
    std::string text = "/* This is\n a multi-line comment */";
    size_t index = 0;
    SToken token;

    // Create an instance of the comment rule
    FCommentRule commentRule;

    // Call the Match function of the comment rule
    bool matchResult = commentRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::Comment);
    ASSERT_EQ(token.lexeme, "/* This is\n a multi-line comment */");
    ASSERT_EQ(index, 35); // Index should be moved to the end of the comment
}

TEST(FCommentRuleTest, NoCommentMatch)
{
    // Initialize test data
    std::string text = "This is not a comment";
    size_t index = 0;
    SToken token;

    // Create an instance of the comment rule
    FCommentRule commentRule;

    // Call the Match function of the comment rule
    bool matchResult = commentRule.Match(text, index, token);

    // Verify the match result
    ASSERT_FALSE(matchResult);
    ASSERT_EQ(index, 0); // Index should remain at the initial position
}
