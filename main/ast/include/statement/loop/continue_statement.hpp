/**
 * @file continue_statement.hpp
 * @brief Declaration of the continue statement class.
 */

#pragma once

#include "statement/interface/statement.hpp"

 /**
  * @brief Represents a continue statement in the abstract syntax tree.
  *
  * This class inherits from the IStatement interface and represents a statement that
  * is used to skip the rest of the current iteration in a loop and jump to the next iteration.
  */
class FContinueStatement final : public IStatement
{
public:

    /**
     * @brief Constructs an FContinueStatement.
     */
    FContinueStatement() = default;

    /**
     * @brief Executes this continue statement.
     *
     * This method is responsible for performing the action associated with the continue statement,
     * which is to skip the rest of the current iteration in a loop and jump to the next iteration.
     * @param context The context in which to execute the continue statement.
     */
    virtual void Execute(const FContext& context) const override;
};
