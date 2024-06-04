#include "statement/try_catch_finally/catch_statement.hpp"

FCatchStatement::FCatchStatement(const std::string& errorVariable, StatementPtr catchBlock)
    : m_errorVariable(errorVariable)
    , m_catchBlock(std::move(catchBlock))
{}

void FCatchStatement::Execute(const FContext& context) const
{
    // Execute the catch block
    m_catchBlock->Execute(context);
}

const std::string& FCatchStatement::GetErrorVariable() const
{
    return m_errorVariable;
}
