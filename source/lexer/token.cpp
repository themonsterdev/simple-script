#include "lexer/token.hpp"

FToken::FToken(
	eTokenType  type,
	std::string lexeme,
	uint32_t    line,
	uint32_t    column)
	: m_type(type)
	, m_lexeme(std::move(lexeme))
	, m_line(line)
	, m_column(column)
{}

void FToken::SetType(eTokenType type)
{
	m_type = type;
}

eTokenType FToken::GetType() const
{
	return m_type;
}

bool FToken::IsSameType(eTokenType type) const
{
	return m_type == type;
}

void FToken::SetLexeme(const std::string& lexeme)
{
	m_lexeme = lexeme;
}

const std::string& FToken::GetLexeme() const
{
	return m_lexeme;
}

bool FToken::IsSameLexeme(const std::string& lexeme) const
{
	return m_lexeme == lexeme;
}

void FToken::SetLine(uint32_t line)
{
	m_line = line;
}

uint32_t FToken::GetLine() const
{
	return m_line;
}

void FToken::SetColumn(uint32_t column)
{
	m_column = column;
}

uint32_t FToken::GetColumn() const
{
	return m_column;
}

bool FToken::IsSameTypeAndLexeme(eTokenType type, const std::string& lexeme) const
{
	return IsSameType(type) && IsSameLexeme(lexeme);
}

std::string FToken::ToString() const
{
	return "Type: " + std::to_string(static_cast<int>(m_type)) + 
		", Lexeme: " + m_lexeme + 
		", Line: " + std::to_string(m_line) + 
		", Column: " + std::to_string(m_column);
}
