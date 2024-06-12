/**
 * @file continue_statement.cpp
 * @brief Implementation of the continue statement class.
 */

// Include the header file for expressions
#include "ast/statement/loop/continue_statement.hpp"

// Include declarations for context objects
#include "context/context.hpp"

void FContinueStatement::Execute(const FContext& context) const
{
    // Signal to the loop control structure to skip the rest of its body and continue with the next iteration
    context.SetContinueFlag(true);
}
