#pragma once

#include <string>
#include <vector>

enum class eTokenType
{
    NUMBER,
    OPERATOR,
    COMPARISON,
	IDENTIFIER,
	KEYWORD,
    END
};

struct SToken
{
	eTokenType type;
	std::string lexeme;
};

class FTokenizer final
{
	std::vector<std::string> m_keywords;
	std::string m_input;
	size_t m_offset;

public:

	FTokenizer(const std::string& input, const std::vector<std::string>& keywords);

	bool HasNextToken();
	SToken PeekNextToken();
	SToken GetNextToken();

private:

	void SkipWhitespace();

	SToken ParseNumber();
	SToken ParseOperator();
	SToken ParseIdentifier();

	static bool IsAlpha(const char c);
	static bool IsNumeric(const char c);
	static bool IsAlphanumeric(const char c);
	static bool IsDelimiter(const char c);
	static bool IsOperator(const char c);
};

std::string TokenTypeToString(eTokenType token);
