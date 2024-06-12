#pragma once

#include "ast/statement/interface/statement.hpp"
#include "ast/statement/block/block_statement.hpp"

class FFinallyStatement final : public IStatement
{
    StatementPtr m_finallyBlock;

public:

    FFinallyStatement(StatementPtr finallyBlock);
    void Execute(const FContext& context) const override;
};
