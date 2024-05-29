/**
 * @file identifier_rule.hpp
 * @brief Declaration of the FIdentifierRule class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary header
#include "rule/interface/lexical_rule.hpp" // For ILexicalRule

/**
 * @brief Rule class for handling identifiers in lexical analysis.
 * This class implements the ILexicalRule interface for matching identifiers in text.
 */
class FIdentifierRule final : public ILexicalRule
{
public:

    /**
     * @brief Matches an identifier in the given text.
     * @param text The text to match against.
     * @param index The index in the text where the matching should start.
     * @param token Output parameter where the matched token will be stored.
     * @return True if the match is successful, false otherwise.
     */
    virtual bool Match(const std::string& text, size_t& index, SToken& token) const override;
};
