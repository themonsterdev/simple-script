/**
 * @file string_format_expression.cpp
 * @brief Implementation of the FStringFormatExpression class.
 */

 // Include the declaration of the FStringFormatExpression class
#include "expression/literal/string_format_expression.hpp"
#include "statement/declaration/var_declaration_statement.hpp"

#include <regex>
#include <sstream>

// Include declarations for context objects
#include "context.hpp"

FStringFormatExpression::FStringFormatExpression(const std::string& value)
    : m_value(value)
{
    // Parse the template expression
    ParseTemplate();
}

std::string FStringFormatExpression::GetValue() const
{
    // Return the string value
    return m_value;
}

void FStringFormatExpression::SetValue(const std::string& value)
{
    // Set the string value
    m_value = value;
}

Value FStringFormatExpression::Evaluate(const FContext& context) const
{
    // Evaluate the template expression
    std::ostringstream oss;
    for (const auto& segment : m_segments)
    {
        if (segment.isLiteral)
        {
            oss << segment.value;
        }
        else
        {
            // Retrieve the variable value from the context and append it to the result
            Value value = context.GetVariable(segment.value);
            if (std::holds_alternative<std::string>(value))
            {
                oss << std::get<std::string>(value);
            }
            else if (std::holds_alternative<int>(value))
            {
                oss << std::get<int>(value);
            }
            // Add more type checks if needed
        }
    }
    return oss.str();
}

void FStringFormatExpression::ParseTemplate()
{
    // Parse the template string into segments
    size_t pos = 0;
    while (pos < m_value.size())
    {
        size_t start = m_value.find("${", pos);
        if (start == std::string::npos)
        {
            // Add the remaining part of the string as a literal segment
            m_segments.push_back({ m_value.substr(pos), true });
            break;
        }
        if (start > pos)
        {
            // Add the preceding literal segment
            m_segments.push_back({ m_value.substr(pos, start - pos), true });
        }
        size_t end = m_value.find("}", start);
        if (end == std::string::npos)
        {
            // Handle error: unmatched "${"
            break;
        }
        // Add the variable segment
        m_segments.push_back({ m_value.substr(start + 2, end - start - 2), false });
        pos = end + 1;
    }
}
