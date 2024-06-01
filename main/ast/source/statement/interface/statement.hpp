/**
 * @file statement.hpp
 * @brief Declaration of the statement interface class.
 */

// Ensure this file is included only once
#pragma once

#include <map>          // For std::map
#include <memory>       // For std::unique_ptr
#include "context.hpp"  // Include declarations for context objects

/**
 * @brief Interface for language statements.
 *
 * This interface defines a contract for language statements, providing a common
 * method for executing statements within a given context.
 */
class IStatement
{
public:

    /**
     * @brief Virtual destructor for proper memory management.
     */
    virtual ~IStatement() = default;

    /**
     * @brief Executes the statement within the given context.
     *
     * This method executes the statement within the provided context.
     *
     * @param context The context in which to execute the statement.
     */
    virtual void Execute(const FContext& context) const = 0;
};

// Define a convenient alias for unique pointers to statements
using StatementPtr  = std::unique_ptr<IStatement>;

// Define a convenient alias for lists of statement pointers
using StatementList = std::list<StatementPtr>;

// Define a convenient alias for vectors of statement pointers
using StatementVector = std::vector<StatementPtr>;
