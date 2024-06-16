/**
 * @file operator_rule.cpp
 * @brief Implementation of the FOperatorRule class.
 */

// Include the header file for the operator rule
#include "lexer/rule/operator_rule.hpp"

// Define the list of assignments
static constexpr auto ASSIGNMENTS =
{
    "=",                // Direct assignment
    "+=", "-=",         // Compound assignment by sum and difference
    "*=", "/=", "%=",   // Compound assignment by product, quotient, and remainder
    "<<=", ">>=",       // Compound assignment by bitwise left shift and right shift
    "&=", "^=", "|=",   // Compound assignment by bitwise AND, XOR, and OR
};

// Define the list of comparisons
static constexpr auto COMPARISONS =
{
    "==",
    "!=",
    "<=",
    ">=",
    "<=>",
};

// Define the list of operators
static constexpr auto OPS =
{
    "++",
    "--",
};

bool FOperatorRule::Match(const std::string& text, size_t& index, FToken& token) const
{
    // Define a string containing the operators
    const std::string operators = "/*-+%=<>^?!.";

    // Check if the current character is one of the operators
    if (operators.find(text[index]) != std::string::npos)
    {
        token.SetType(eTokenType::Operator);
        token.SetLexeme(text.substr(index, 1));

        for (const auto& assignment : ASSIGNMENTS)
        {
            if (token.GetLexeme()[0] != assignment[0])
            {
                continue;
            }

            size_t size = strlen(assignment);

            if (text.substr(index, size) == assignment)
            {
                token.SetLexeme(assignment);
                index += size - 1;
                break;
            }
        }

        for (const auto& comparison : COMPARISONS)
        {
            if (token.GetLexeme()[0] != comparison[0])
            {
                continue;
            }

            size_t size = strlen(comparison);

            if (text.substr(index, size) == comparison)
            {
                token.SetLexeme(comparison);
                index += size - 1;
                break;
            }
        }

        for (const auto& op : OPS)
        {
            if (token.GetLexeme()[0] != op[0])
            {
                continue;
            }

            size_t size = strlen(op);

            if (text.substr(index, size) == op)
            {
                token.SetLexeme(op);
                index += size - 1;
                break;
            }
        }

        // Move to the next character
        index++;

        // Return true to indicate a successful match
        return true;
    }

    // Return false if the current character is not an operator
    return false;
}
