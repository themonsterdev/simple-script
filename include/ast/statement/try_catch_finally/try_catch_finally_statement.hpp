#pragma once

#include "ast/statement/interface/statement.hpp"
#include "ast/statement/block/block_statement.hpp"
#include "ast/statement/try_catch_finally/try_statement.hpp"
#include "ast/statement/try_catch_finally/catch_statement.hpp"
#include "ast/statement/try_catch_finally/finally_statement.hpp"

class FTryCatchFinallyStatement final : public IStatement
{
    FTryStatement m_tryStatement;
    FCatchStatement m_catchStatement;
    FFinallyStatement m_finallyStatement;

public:

    FTryCatchFinallyStatement(
        StatementPtr tryBlock,
        const std::string& errorVariable,
        StatementPtr catchBlock,
        StatementPtr finallyBlock
    );

    void Execute(const FContext& context) const override;
};
