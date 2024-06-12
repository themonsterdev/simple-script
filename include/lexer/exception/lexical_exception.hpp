/**
 * @file lexical_exception.hpp
 * @brief Declaration of the FLexicalException class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary libraries
#include <stdexcept> // For std::runtime_error
#include <string>    // For std::string

/**
 * @brief Exception class for lexical analysis errors.
 * This class is used to handle errors that occur during the lexical analysis phase.
 */
class FLexicalException : public std::runtime_error
{
    // Stores the error message
    std::string m_message;

public:

    /**
     * @brief Constructs a new FLexicalException with a given message.
     * @param message The error message.
     */
    explicit FLexicalException(const std::string& message)
        : std::runtime_error(message)
    {}
};
