#include "ast/statement/oop/member_declaration_statement.hpp"
#include "context/context.hpp"
#include <stdexcept>

FMemberDeclarationStatement::FMemberDeclarationStatement(
    Visibility visibility,
    StatementPtr statement)
    : m_visibility(visibility)
    , m_statement(std::move(statement))
{}

void FMemberDeclarationStatement::Execute(const FContext& context) const
{
    m_statement->Execute(context);
}

Visibility FMemberDeclarationStatement::GetVisibility() const
{
    return m_visibility;
}

const StatementPtr& FMemberDeclarationStatement::GetStatement() const
{
    return m_statement;
}
