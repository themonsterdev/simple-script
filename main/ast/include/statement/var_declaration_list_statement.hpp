#pragma once

#include "statement/interface/statement.hpp"

class FVarDeclarationListStatement : public IStatement
{
	StatementVector m_declarations;

public:

    FVarDeclarationListStatement(StatementVector declarations);

    virtual void Execute(const FContext& context) const override;

    const StatementVector& GetDeclarations() const;
};
