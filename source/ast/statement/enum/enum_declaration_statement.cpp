/**
 * @file enum_declaration_statement.cpp
 * @brief Implementation of the enum declaration statement class.
 */

#include "ast/statement/enum/enum_declaration_statement.hpp"

FEnumDeclarationStatement::FEnumDeclarationStatement(
    EnumDefinitionPtr enumDefinition,
    ExpressionList expressions)
    : m_enumDefinition(enumDefinition)
    , m_expressions(std::move(expressions))
{}

void FEnumDeclarationStatement::Execute(const FContext& context) const
{
    printf("FEnumDeclarationStatement::Execute\n");

    for (const auto& expression : m_expressions)
    {
        const auto& value = expression->Evaluate(context);

        if (!value)
        {
            continue;
        }

        if (value->IsNumber())
        {
            printf("%s\n", value->ToString().c_str());
        }
        else
        {
            // throw error
        }
    }

    for (const auto& value : m_enumDefinition->GetValues())
    {
        // value.second->SetDefaultValue(nullptr);
    }
}
