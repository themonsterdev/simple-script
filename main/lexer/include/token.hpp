/**
 * @file token.hpp
 * @brief Declaration of token-related structures and enumerations.
 */

// Ensure this file is included only once
#pragma once

#include <vector>  // For std::vector
#include <string>  // For std::string

/**
 * @enum eTokenType
 * @brief Enumeration of the different types of tokens.
 */
enum class eTokenType
{
	// Identifiers
	Identifier,  // Identifier token
	Keyword,     // Keyword token

	// Operators
	Operator,    // Operator token
	Comparison,  // Comparison operator token

	// Delimiters/Punctuators
	Punctuation, // Punctuation token
	Delimiter,   // Delimiter token

	// Literals
	Number,					// Number literal token
	Float,					// Float literal token
	String,					// String literal token
	StringFormatLiteral,	// String format literal token
	Boolean,				// Boolean literal token

	// Comments
	Comment,     // Comment token

	// Others
	Whitespace,	// Whitespace token
	End,		// End of input token
	Unknown		// Unknown token
};

/**
 * @struct SToken
 * @brief Structure representing a token.
 */
struct SToken
{
	eTokenType type;	// Type of the token
	std::string lexeme;	// Lexeme of the token
	uint32_t line;		// Line number where the token occurs
	uint32_t column;	// Column number where the token occurs
};

// Alias for a vector of tokens
using TokenVector = std::vector<SToken>;
