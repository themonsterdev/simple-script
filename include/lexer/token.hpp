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
 * @class FToken
 * @brief Class representing a token.
 */
class FToken final
{
	eTokenType  m_type;		// Type of the token
	std::string m_lexeme;	// Lexeme of the token
	uint32_t    m_line;		// Line number where the token occurs
	uint32_t    m_column;	// Column number where the token occurs

public:

	FToken() = default;
	FToken(
		eTokenType  type,
		std::string lexeme,
		uint32_t    line,
		uint32_t    column
	);

	void SetType(eTokenType type);
	eTokenType GetType() const;
	bool IsSameType(eTokenType type) const;

	void SetLexeme(const std::string& lexeme);
	const std::string& GetLexeme() const;
	bool IsSameLexeme(const std::string& lexeme) const;

	void SetLine(uint32_t line);
	uint32_t GetLine() const;

	void SetColumn(uint32_t column);
	uint32_t GetColumn() const;

	bool IsSameTypeAndLexeme(
		eTokenType type,
		const std::string& lexeme
	) const;

	std::string ToString() const;
};

// Alias for a vector of tokens
using TokenVector = std::vector<FToken>;
