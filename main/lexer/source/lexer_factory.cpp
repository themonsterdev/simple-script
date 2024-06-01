/**
 * @file lexer_factory.cpp
 * @brief Implementation of the FLexerFactory class.
 */

// Include the header file for the lexer factory
#include "lexer_factory.hpp"

// Include header files for lexical rules
#include "rule/boolean_rule.hpp"
#include "rule/comment_rule.hpp"
#include "rule/delimiter_rule.hpp"
#include "rule/identifier_rule.hpp"
#include "rule/number_rule.hpp"
#include "rule/operator_rule.hpp"
#include "rule/punctuation_rule.hpp"
#include "rule/string_rule.hpp"

LexicalRuleVector FLexerFactory::CreateRules()
{
    // Vector to store lexical rules
    LexicalRuleVector rules;

    // Add each lexical rule to the vector
    rules.push_back(std::make_unique<FBooleanRule>());
    rules.push_back(std::make_unique<FCommentRule>());
    rules.push_back(std::make_unique<FDelimiterRule>());
    rules.push_back(std::make_unique<FIdentifierRule>());
    rules.push_back(std::make_unique<FNumberRule>());
    rules.push_back(std::make_unique<FOperatorRule>());
    rules.push_back(std::make_unique<FPunctuationRule>());
    rules.push_back(std::make_unique<FStringRule>());
    // Add other lexical rules here.

    // Return the vector of lexical rules
    return rules;
}
