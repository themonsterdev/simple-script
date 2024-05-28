#pragma once

#include <string>
#include <vector>

#include "comment.hpp"

/**
 * @enum eTokenType
 * @brief Enumeration of the different types of tokens.
 */
enum class eTokenType
{
	// Identifiers
	IDENTIFIER,  // Identifier token
	KEYWORD,     // Keyword token

	// Operators
	OPERATOR,    // Operator token
	COMPARISON,  // Comparison operator token

	// Delimiters/Punctuators
	PUNCTUATION, // Punctuation token
	DELIMITER,   // Delimiter token

	// Literals
	NUMBER,      // Number literal token
	FLOAT,       // Float literal token
	STRING,      // String literal token
	BOOLEAN,     // Boolean literal token

	// Comments
	COMMENT,     // Comment token

	// Others
	END			// End of input token
};

/**
 * @struct SToken
 * @brief Structure representing a token.
 */
struct SToken
{
	eTokenType type;	// The type of the token
	std::string lexeme;	// The lexeme of the token
};

/**
 * @class FTokenizer
 * @brief Class for tokenizing source code.
 */
class FTokenizer final
{
	std::vector<std::string> m_keywords;	// List of keywords
	std::string m_input;					// Source code input
	size_t m_offset;						// Current offset in the source code
	FCommentHandler m_commentHandler;		// Comment handler

public:

	/**
	 * @brief Constructor that takes the source code input and a list of keywords.
	 * @param input The source code input.
	 * @param keywords The list of keywords.
	 */
	FTokenizer(const std::string& input, const std::vector<std::string>& keywords);
	
	/**
	 * @brief Constructor that takes the source code input, a list of keywords, and a list of comments.
	 * @param input The source code input.
	 * @param keywords The list of keywords.
	 * @param comments The list of comments.
	 */
	FTokenizer(const std::string& input, const std::vector<std::string>& keywords, const std::vector<SComment>& comments);

	/**
	 * @brief Checks if there are more tokens to process.
	 * @return True if there are more tokens, false otherwise.
	 */
	bool HasNextToken();

	/**
	 * @brief Returns the next token without consuming it.
	 * @return The next token.
	 */
	SToken PeekNextToken();

	/**
	 * @brief Returns and consumes the next token.
	 * @return The next token.
	 */
	SToken GetNextToken();

private:

	/**
	 * @brief Skips whitespace characters in the input.
	 */
	void SkipWhitespace();

	/**
	* @brief Parses a number token.
	* @return The parsed number token.
	*/
	SToken ParseNumber();

	/**
	 * @brief Parses a string token.
	 * @return The parsed string token.
	 */
	SToken ParseString();

	/**
	 * @brief Parses an operator token.
	 * @return The parsed operator token.
	 */
	SToken ParseOperator();

	/**
	 * @brief Parses an punctuation token.
	 * @return The parsed punctuation token.
	 */
	SToken ParsePunctuation();

	/**
	 * @brief Parses an identifier token.
	 * @return The parsed identifier token.
	 */
	SToken ParseIdentifier();

	/**
	 * @brief Parses a comment token.
	 * @return The parsed comment token.
	 */
	SToken ParseComment();

	/**
	 * @brief Checks if a character is a comment.
	 * @param c The character to check.
	 * @return True if the character is a comment, false otherwise.
	 */
	bool IsComment(const char c);
};

/**
 * @brief Converts a token type to a string representation.
 * @param token The token type to convert.
 * @return The string representation of the token type.
 */
std::string TokenTypeToString(const eTokenType& token);
