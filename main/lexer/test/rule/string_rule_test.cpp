#include "gtest/gtest.h"                    // Include Google Test framework
#include "rule/string_rule.hpp"             // Include the string rule header file
#include "exception/lexical_exception.hpp"

TEST(FStringRuleTest, StringMatch)
{
    // Initialize test data
    std::string text = "'Hello, world!'";
    size_t index = 0;
    SToken token;

    // Create an instance of the string rule
    FStringRule stringRule;

    // Call the Match function of the string rule
    bool matchResult = stringRule.Match(text, index, token);

    // Verify the match result
    ASSERT_TRUE(matchResult);
    ASSERT_EQ(token.type, eTokenType::String);
    ASSERT_EQ(token.lexeme, "Hello, world!");
    ASSERT_EQ(index, text.size()); // Index should be moved to the end of the string
}

TEST(FStringRuleTest, UnterminatedString)
{
    // Initialize test data
    std::string text = "\"Hello, world!";
    size_t index = 0;
    SToken token;

    // Create an instance of the string rule
    FStringRule stringRule;

    // Call the Match function of the string rule
    try
    {
        stringRule.Match(text, index, token);
        // The Match function should throw a LexicalException for an unterminated string
        FAIL() << "Expected LexicalException for unterminated string";
    }
    catch (const FLexicalException& e)
    {
        // Verify that the exception message is correct
        ASSERT_STREQ(e.what(), "Unterminated string literal");
    }
    catch (...)
    {
        // If an exception other than LexicalException is thrown, fail the test
        FAIL() << "Expected LexicalException for unterminated string";
    }
}
