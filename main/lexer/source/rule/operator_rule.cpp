/**
 * @file operator_rule.cpp
 * @brief Implementation of the FOperatorRule class.
 */

// Include the header file for the operator rule
#include "rule/operator_rule.hpp"

bool FOperatorRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    // Define a string containing the operators
    const std::string operators = "/*-+%=";

    // Check if the current character is one of the operators
    if (operators.find(text[index]) != std::string::npos)
    {
        // Set token type to Operator
        token.type = eTokenType::Operator;

        // Set token lexeme to the current character
        token.lexeme = text.substr(index, 1);

        // Move to the next character
        index++;

        // Return true to indicate a successful match
        return true;
    }

    // Return false if the current character is not an operator
    return false;
}
