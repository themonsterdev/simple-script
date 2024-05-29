/**
 * @file lexical_rule.hpp
 * @brief Declaration of the ILexicalRule interface class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary libraries
#include <vector> // For std::vector
#include <memory> // For std::unique_ptr
#include <string> // For std::string

// Include custom header
#include "token.hpp" // For SToken

/**
 * @brief Interface class for lexical rules.
 * This class defines the interface for lexical rules used during lexical analysis.
 */
class ILexicalRule
{
public:

    /**
     * @brief Virtual destructor for proper memory management.
     */
    virtual ~ILexicalRule() = default;

    /**
     * @brief Matches a portion of text against the lexical rule.
     * @param text The text to match against.
     * @param index The index in the text where the matching should start.
     * @param token Output parameter where the matched token will be stored.
     * @return True if the match is successful, false otherwise.
     */
    virtual bool Match(const std::string& text, size_t& index, SToken& token) const = 0;
};

// Define a convenient alias for unique pointers to lexical rule
using LexicalRulePtr = std::unique_ptr<ILexicalRule>;

// Define a convenient alias for vectors of lexical rule pointers
using LexicalRuleVector = std::vector<LexicalRulePtr>;
