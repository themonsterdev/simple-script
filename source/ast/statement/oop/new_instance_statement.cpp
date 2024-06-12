#include "ast/statement/oop/new_instance_statement.hpp"
#include "context/context.hpp"
#include "value/string_value.hpp"

FNewInstanceStatement::FNewInstanceStatement(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

void FNewInstanceStatement::Execute(const FContext& context) const
{
    const auto& value = m_expression->Evaluate(context);

    if (value && value->IsString())
    {
        const auto& string = std::dynamic_pointer_cast<FStringValue>(value);
        const auto& name = string->GetValue();
        printf("string=%s\n", name.c_str());

        // context.GetClassDefinition(name);
    }
}

const ExpressionPtr& FNewInstanceStatement::GetExpression() const
{
    return m_expression;
}
