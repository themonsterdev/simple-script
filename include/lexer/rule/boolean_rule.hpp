/**
 * @file boolean_rule.hpp
 * @brief Declaration of the FBooleanRule class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary header
#include "lexer/rule/interface/lexical_rule.hpp" // For ILexicalRule

/**
 * @brief Rule class for handling booleans in lexical analysis.
 * This class implements the ILexicalRule interface for matching booleans in text.
 */
class FBooleanRule final : public ILexicalRule
{
public:

    /**
     * @brief Matches a boolean in the given text.
     * @param text The text to match against.
     * @param index The index in the text where the matching should start.
     * @param token Output parameter where the matched token will be stored.
     * @return True if the match is successful, false otherwise.
     */
    bool Match(const std::string& text, size_t& index, FToken& token) const override;
};
