#include "ast/statement/try_catch_finally/try_catch_finally_statement.hpp"
#include "context/context.hpp"
#include "value/string_value.hpp"

FTryCatchFinallyStatement::FTryCatchFinallyStatement(
    StatementPtr tryBlock,
    const std::string& errorVariable,
    StatementPtr catchBlock,
    StatementPtr finallyBlock
) 
    : m_tryStatement(std::move(tryBlock))
    , m_catchStatement(errorVariable, std::move(catchBlock))
    , m_finallyStatement(std::move(finallyBlock))
{}

void FTryCatchFinallyStatement::Execute(const FContext& context) const
{
    try {
        // Execute the try block
        m_tryStatement.Execute(context);

        if (context.GetThrowFlag())
        {
            context.SetThrowFlag(false);
        }
    }
    catch (const std::exception& e) {
        // Assign error to the error variable
        context.AddSymbol(
            m_catchStatement.GetErrorVariable(),
            std::make_shared<FStringValue>(e.what())
        );

        // Execute the catch block
        m_catchStatement.Execute(context);
    }
    
    // Execute the finally block
    m_finallyStatement.Execute(context);
}
