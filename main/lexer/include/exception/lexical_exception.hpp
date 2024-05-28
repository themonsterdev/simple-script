#pragma once

#include <exception>
#include <string>

class FLexicalException : public std::exception
{
    std::string m_message;

public:

    explicit FLexicalException(const std::string& message)
        : m_message(message)
    {}

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }
};
