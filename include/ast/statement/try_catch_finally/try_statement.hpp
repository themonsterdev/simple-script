#pragma once

#include "ast/statement/interface/statement.hpp"
#include "ast/statement/block/block_statement.hpp"

class FTryStatement final : public IStatement
{
    StatementPtr m_tryBlock;

public:

    FTryStatement(StatementPtr tryBlock);

    void Execute(const FContext& context) const override;
};
