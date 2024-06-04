#pragma once

#include "statement/interface/statement.hpp"
#include "statement/block/block_statement.hpp"

class FFinallyStatement final : public IStatement
{
    StatementPtr m_finallyBlock;

public:

    FFinallyStatement(StatementPtr finallyBlock);
    virtual void Execute(const FContext& context) const override;
};
