/**
 * @file lexer_factory.hpp
 * @brief Declaration of the FLexerFactory class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary header
#include "rule/interface/lexical_rule.hpp" // For LexicalRuleVector

/**
 * @brief Factory class for creating lexical rules.
 * This class provides a static method to create and return a vector of lexical rules.
 */
class FLexerFactory final
{
public:

    /**
     * @brief Creates and returns a vector of lexical rules.
     * @return A vector of lexical rules.
     */
    static LexicalRuleVector CreateRules();
};
