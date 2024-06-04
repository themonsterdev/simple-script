#include "statement/try_catch_finally/try_statement.hpp"
#include "context.hpp"

FTryStatement::FTryStatement(StatementPtr tryBlock)
    : m_tryBlock(std::move(tryBlock))
{}

void FTryStatement::Execute(const FContext& context) const
{
    // Execute the try block
    m_tryBlock->Execute(context);
}
