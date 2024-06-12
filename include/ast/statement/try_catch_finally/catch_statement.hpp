#pragma once

#include "ast/statement/interface/statement.hpp"
#include "ast/statement/block/block_statement.hpp"

class FCatchStatement final : public IStatement
{
    std::string m_errorVariable;
    StatementPtr m_catchBlock;

public:

    FCatchStatement(const std::string& errorVariable, StatementPtr catchBlock);
    void Execute(const FContext& context) const override;

    const std::string& GetErrorVariable() const;
};
