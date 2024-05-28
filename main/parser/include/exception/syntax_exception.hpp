#pragma once

#include <exception>
#include <string>

class FSyntaxException final : public std::exception
{
    std::string m_message;

public:

    explicit FSyntaxException(const std::string& message)
        : m_message(message)
    {}

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }
};
