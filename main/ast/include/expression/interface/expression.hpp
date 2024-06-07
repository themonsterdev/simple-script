/**
 * @file expression.hpp
 * @brief Declaration of the expression class.
 */

// Ensure this file is included only once
#pragma once

#include <list>         // For std::list
#include <memory>       // For std::unique_ptr
#include "scope.hpp"
#include "interface/value.hpp"

class FContext;

/**
 * @brief An interface representing an expression in the abstract syntax tree (AST).
 *
 * This interface defines a contract for expression nodes in the AST, requiring them to
 * provide a method for evaluating the expression within a given context.
 */
class IExpression
{
public:

    /**
     * @brief Virtual destructor for proper memory management.
     */
    virtual ~IExpression() = default;

    /**
     * @brief Evaluates the expression within the given context.
     *
     * This method evaluates the expression node within the provided context, which
     * represents the scope and variables accessible during evaluation, and returns
     * the resulting value.
     *
     * @param context The context representing the scope and variables accessible
     *                during evaluation.
     * @return The evaluated value of the expression.
     */
    virtual ValuePtr Evaluate(const FContext& context) const = 0; 
};

// Define a convenient alias for unique pointers to expressions
using ExpressionPtr = std::unique_ptr<IExpression>;

// Define a convenient alias for lists of expression pointers
using ExpressionList = std::list<ExpressionPtr>;
