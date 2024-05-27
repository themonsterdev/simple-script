#include "tokenizer.hpp"
#include <stdexcept>

/**
 * @brief Checks if a character is a numeric character.
 * @param c The character to check.
 * @return True if the character is numeric, false otherwise.
 */
static bool IsNumeric(const char c)
{
    return c >= '0' && c <= '9';
}

/**
 * @brief Checks if a character is an alphabetic character.
 * @param c The character to check.
 * @return True if the character is alphabetic, false otherwise.
 */
static bool IsAlpha(const char c)
{
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || c == '_';
}

/**
 * @brief Checks if a character is alphanumeric.
 * @param c The character to check.
 * @return True if the character is alphanumeric, false otherwise.
 */
static bool IsAlphanumeric(const char c)
{
    return IsAlpha(c) || IsNumeric(c);
}

/**
 * @brief Checks if a character is a delimiter.
 * @param c The character to check.
 * @return True if the character is a delimiter, false otherwise.
 */
static bool IsDelimiter(const char c)
{
    return c == ' ' || c == '\r' || c == '\n';
}

/**
 * @brief Checks if a character is an operator.
 * @param c The character to check.
 * @return True if the character is an operator, false otherwise.
 */
static bool IsOperator(const char c)
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

/**
 * @brief Checks if a character is an quote.
 * @param c The character to check.
 * @return True if the character is an quote, false otherwise.
 */
static bool IsQuote(const char c)
{
    switch (c)
    {
    case '"':
    case '\'':
    case '`':
        return true;
    }
    return false;
}

FTokenizer::FTokenizer(const std::string& input, const std::vector<std::string>& keywords)
	: m_input(input)
	, m_keywords(keywords)
	, m_offset(0)
{}

FTokenizer::FTokenizer(const std::string& input, const std::vector<std::string>& keywords, const std::vector<SComment>& comments)
    : m_input(input)
    , m_keywords(keywords)
    , m_offset(0)
    , m_commentHandler(comments)
{}

bool FTokenizer::HasNextToken()
{
    // If the offset is less than the input size
    if (m_offset < m_input.size())
    {
        // If the current character is a comment
        if (IsComment(m_input[m_offset]))
        {
            // If the comment should be ignored
            if (m_commentHandler.ShouldIgnore(m_input[m_offset]))
            {
                // Parse the comment and skip whitespace
                ParseComment();
                SkipWhitespace();

                // Return whether there are more tokens
                return m_offset < m_input.size();
            }
        }

        // Return true if there are more tokens
        return true;
    }

    // Return false if there are no more tokens
    return false;
}

SToken FTokenizer::GetNextToken()
{
    // Skip whitespace
	SkipWhitespace();

    // If there are no more tokens, return an end token
    if (!HasNextToken())
    {
        return { eTokenType::END, "" };
    }

    // If the current character is a comment, parse it
    if (IsComment(m_input[m_offset]))
    {
        return ParseComment();
    }

    // If the current character is numeric, parse a number
    if (IsNumeric(m_input[m_offset]))
    {
        return ParseNumber();
    }

    // If the current character is a double quote, parse a string
    if (IsQuote(m_input[m_offset])) // @TODO Same system with comment ?
    {
        return ParseString();
    }

    // If the current character is alphabetic, parse an identifier
    if (IsAlpha(m_input[m_offset]))
    {
        return ParseIdentifier();
    }

    // If the current character is an operator, parse an operator
    if (IsOperator(m_input[m_offset]))
    {
        return ParseOperator();
    }

    // Throw an exception if the token cannot be parsed
    throw std::exception("Failed to get next token");
}

SToken FTokenizer::PeekNextToken()
{
    size_t startPos = m_offset;         // Save the current offset
    SToken nextToken = GetNextToken();  // Get the next token
    if (startPos != m_offset)           // Restore the offset
        m_offset = startPos;
    return nextToken;                   // Return the next token
}

void FTokenizer::SkipWhitespace()
{
    // While there are more tokens
    while (HasNextToken())
    {
        // If the current character is not a delimiter, exit the loop
        if (!IsDelimiter(m_input[m_offset]))
        {
            break;
        }

        // Increment the offset to skip the delimiter
        m_offset++;
    }
}

SToken FTokenizer::ParseNumber()
{
    // Save the starting position
    size_t startPos = m_offset;

    // While there are more numeric characters
    while (HasNextToken())
    {
        // If the current character is not numeric, exit the loop
        if (!IsNumeric(m_input[m_offset]))
        {
            break;
        }

        // Increment the offset to include the numeric character
        m_offset++;
    }

    // Return the number token with the substring of the numeric characters
    return {
        eTokenType::NUMBER,
        m_input.substr(startPos, m_offset - startPos)
    };
}

SToken FTokenizer::ParseString()
{
    // Save the starting position
    size_t startPos = m_offset;

    // Get the initial quote character
    char quoteChar = m_input[m_offset++];

    // While there are more characters in the string and it is not terminated
    while (HasNextToken() && m_input[m_offset] != quoteChar)
    {
        // If the current character is an escape character
        if (m_input[m_offset] == '\\' && m_offset + 1 < m_input.size())
        {
            // Move two characters ahead to skip the escape sequence
            m_offset += 2;
        }
        else
        {
            // Move to the next character in the string
            m_offset++;
        }
    }

    // If the end of the string is reached without finding the ending quote
    if (m_offset >= m_input.size() || m_input[m_offset] != quoteChar)
    {
        // Throw an exception for unterminated string literal
        throw std::runtime_error("Unterminated string literal");
    }
    else
    {
        // Move beyond the string delimiter
        m_offset++;
    }

    // Return the string token excluding the quotes
    return {
        eTokenType::STRING,
        m_input.substr(startPos + 1, m_offset - startPos - 2)
    };
}

SToken FTokenizer::ParseOperator()
{
    // If there are more tokens
    if (HasNextToken())
    {
        // Create an operator token with the current character
        std::string op(1, m_input[m_offset]);

        // Increment the offset to move to the next character
        m_offset++;

        // Return the operator token
        return {
            eTokenType::OPERATOR,
            op
        };
    }

    // Return an end token if there are no more tokens
    return {
        eTokenType::END,
        ""
    };
}

SToken FTokenizer::ParseIdentifier()
{
    // Save the starting position
    size_t startPos = m_offset;

    // While there are more tokens
    while (HasNextToken())
    {
        // If the current character is not alphanumeric, exit the loop
        if (!IsAlphanumeric(m_input[m_offset]))
        {
            break;
        }

        // Increment the offset to include the alphanumeric character
        m_offset++;
    }

    // Set the default token type to identifier
    eTokenType type = eTokenType::IDENTIFIER;

    // Extract the lexeme from the input string
    std::string lexeme(m_input.substr(startPos, m_offset - startPos));

    // Check if the lexeme matches any keyword
    for (const auto& keyword : m_keywords)
    {
        // If a keyword match is found, set the token type to keyword
        if (lexeme == keyword)
        {
            type = eTokenType::KEYWORD;
            break;
        }
    }

    // Return the token with the determined type and lexeme
    return { type, lexeme };
}

SToken FTokenizer::ParseComment()
{
    // String to store the extracted comment
    std::string extractedComment;

    // Browse all comment types
    for (const auto& comment : m_commentHandler.GetComments())
    {
        // Check if the current character matches the start of a comment
        if (m_input.substr(m_offset, comment.startDelim.size()) == comment.startDelim)
        {
            // If yes, check if the comment is on a single line or on multiple lines
            if (comment.type == eCommentType::SINGLE_LINE)
            {
                // If it's a single line comment, extract the comment to the end of the line
                while (m_offset < m_input.size() && m_input[m_offset] != '\n')
                {
                    extractedComment += m_input[m_offset++];
                }
            }
            else if (comment.type == eCommentType::MULTI_LINE)
            {
                // If it's a multi-line comment, extract the comment to the end of comment delimiter
                while (m_offset + comment.endDelim.size() <= m_input.size())
                {
                    // Check if the end of the comment is found
                    if (m_input.substr(m_offset, comment.endDelim.size()) == comment.endDelim)
                    {
                        // Include the end delimiter in the extracted comment
                        extractedComment += m_input.substr(m_offset, comment.endDelim.size());

                        // Move past end of comment delimiter
                        m_offset += comment.endDelim.size();
                        break;
                    }
                    
                    // Otherwise, continue extracting comment content
                    extractedComment += m_input[m_offset++];
                }
            }

            // Return extracted comment as a token
            return {
               eTokenType::COMMENT,
               extractedComment
            };
        }
    }

    // If no comments were found, return an empty token
    return { eTokenType::END, "" };
}

bool FTokenizer::IsComment(const char c)
{
    return m_commentHandler.IsComment(c);
}

std::string TokenTypeToString(const eTokenType& token)
{
    switch (token)
    {
    case eTokenType::NUMBER:
        return "NUMBER";
    case eTokenType::STRING:
        return "STRING";
    case eTokenType::OPERATOR:
        return "OPERATOR";
    case eTokenType::COMPARISON:
        return "COMPARISON";
    case eTokenType::IDENTIFIER:
        return "IDENTIFIER";
    case eTokenType::KEYWORD:
        return "KEYWORD";
    case eTokenType::COMMENT:
        return "COMMENT";
    case eTokenType::END:
        return "END";
    }
    return "Unknow";
}
