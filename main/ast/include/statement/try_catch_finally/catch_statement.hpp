#pragma once

#include "statement/interface/statement.hpp"
#include "statement/block/block_statement.hpp"

class FCatchStatement final : public IStatement
{
    std::string m_errorVariable;
    StatementPtr m_catchBlock;

public:

    FCatchStatement(const std::string& errorVariable, StatementPtr catchBlock);
    virtual void Execute(const FContext& context) const override;

    const std::string& GetErrorVariable() const;
};
