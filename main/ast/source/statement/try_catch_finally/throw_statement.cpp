#include "statement/try_catch_finally/throw_statement.hpp"
#include "context.hpp"
#include <stdexcept>
#include <iostream>

FThrowStatement::FThrowStatement(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

void FThrowStatement::Execute(const FContext& context) const
{
    if (m_expression)
    {
        Value value = m_expression->Evaluate(context);

        // Vérifie si la valeur est une chaîne (le message d'erreur)
        if (std::holds_alternative<std::string>(value))
        {
            // Jette une exception de type std::runtime_error avec le message d'erreur
            // throw std::runtime_error(std::get<std::string>(value));

            std::cout << std::get<std::string>(value) << std::endl;

            context.SetThrowFlag(true);
        }
        else
        {
            // Si la valeur n'est pas une chaîne, jette une exception par défaut
            throw std::runtime_error("Unhandled exception occurred.");
        }
    }
}
