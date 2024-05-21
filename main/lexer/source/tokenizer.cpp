#include "tokenizer.hpp"

FTokenizer::FTokenizer(const std::string& input, const std::vector<std::string>& keywords)
	: m_input(input)
	, m_keywords(keywords)
	, m_offset(0)
{}

bool FTokenizer::HasNextToken()
{
    return m_offset < m_input.size();
}

SToken FTokenizer::GetNextToken()
{
	SkipWhitespace();

    if (!HasNextToken())
    {
        return { eTokenType::END, "" };
    }

    if (IsNumeric(m_input[m_offset]))
    {
        return ParseNumber();
    }

    if (IsAlpha(m_input[m_offset]))
    {
        return ParseIdentifier();
    }

    if (IsOperator(m_input[m_offset]))
    {
        return ParseOperator();
    }

    throw std::exception("Failed to get next token");
}

SToken FTokenizer::PeekNextToken()
{
    size_t startPos = m_offset;
    SToken nextToken = GetNextToken();
    if (startPos != m_offset)
        m_offset = startPos;
    return nextToken;
}

void FTokenizer::SkipWhitespace()
{
    while (HasNextToken())
    {
        if (!IsDelimiter(m_input[m_offset]))
        {
            break;
        }

        m_offset++;
    }
}

SToken FTokenizer::ParseNumber()
{
    size_t startPos = m_offset;

    while (HasNextToken())
    {
        if (!IsNumeric(m_input[m_offset]))
        {
            break;
        }

        m_offset++;
    }

    SkipWhitespace();

    return {
        eTokenType::NUMBER,
        m_input.substr(startPos, m_offset - startPos)
    };
}

SToken FTokenizer::ParseOperator()
{
    if (HasNextToken())
    {
        std::string op(1, m_input[m_offset]);
        m_offset++;

        return {
            eTokenType::OPERATOR,
            op
        };
    }

    SkipWhitespace();

    return {
        eTokenType::END,
        ""
    };
}

SToken FTokenizer::ParseIdentifier()
{
    size_t startPos = m_offset;

    while (HasNextToken())
    {
        if (!IsAlphanumeric(m_input[m_offset]))
        {
            break;
        }

        m_offset++;
    }

    eTokenType type = eTokenType::IDENTIFIER;
    std::string lexeme(m_input.substr(startPos, m_offset - startPos));

    for (std::string keyword : m_keywords)
    {
        if (lexeme == keyword)
        {
            type = eTokenType::KEYWORD;
            break;
        }
    }

    SkipWhitespace();

    return { type, lexeme };
}

bool FTokenizer::IsNumeric(const char c)
{
    return c >= '0' && c <= '9';
}

bool FTokenizer::IsAlpha(const char c)
{
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || c == '_';
}

bool FTokenizer::IsAlphanumeric(const char c)
{
    return IsAlpha(c) || IsNumeric(c);
}

bool FTokenizer::IsDelimiter(const char c)
{
    return c == ' ' || c == '\n';
}

bool FTokenizer::IsOperator(const char c)
{
    switch (c)
    {
    case '/':
    case '*':
    case '-':
    case '+':
    case '%':
    case '=':
        return true;
    }
    return false;
}

std::string TokenTypeToString(eTokenType token)
{
    switch (token)
    {
    case eTokenType::NUMBER:
        return "NUMBER";
    case eTokenType::OPERATOR:
        return "OPERATOR";
    case eTokenType::COMPARISON:
        return "COMPARISON";
    case eTokenType::IDENTIFIER:
        return "IDENTIFIER";
    case eTokenType::KEYWORD:
        return "KEYWORD";
    case eTokenType::END:
        return "END";
    }
    return "Unknow";
}
