#pragma once

#include "statement/interface/statement.hpp"
#include "statement/block/block_statement.hpp"

class FTryStatement final : public IStatement
{
    StatementPtr m_tryBlock;

public:

    FTryStatement(StatementPtr tryBlock);
    virtual void Execute(const FContext& context) const override;
};
