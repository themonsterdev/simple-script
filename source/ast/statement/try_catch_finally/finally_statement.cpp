#include "ast/statement/try_catch_finally/finally_statement.hpp"

FFinallyStatement::FFinallyStatement(StatementPtr finallyBlock)
    : m_finallyBlock(std::move(finallyBlock))
{}

void FFinallyStatement::Execute(const FContext& context) const
{
    // Execute the finally block
    if (m_finallyBlock)
    {
        m_finallyBlock->Execute(context);
    }
}
