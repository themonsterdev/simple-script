/**
 * @file syntax_exception.hpp
 * @brief Declaration of the FSyntaxException class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary libraries
#include <stdexcept> // For std::runtime_error
#include <string>    // For std::string

/**
 * @brief Exception class for syntax errors.
 *
 * This class inherits from std::runtime_error and represents an exception
 * specifically for syntax errors encountered during interpretation.
 */
class FSyntaxException final : public std::runtime_error
{
public:

    /**
     * @brief Construct a new FSyntaxException object with the given message.
     *
     * @param message The error message describing the syntax error.
     */
    explicit FSyntaxException(const std::string& message)
        : std::runtime_error(message)
    {}
};
