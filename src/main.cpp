#include <iostream>

#include "expressions.hpp"

int main()
{
    FNumberExpression number_expression_1{ 3 };
    FNumberExpression number_expression_2{ 4 };

    FArithmeticExpression arithmetic_expression{
        '+',
        &number_expression_1,
        &number_expression_2
    };

    int value = arithmetic_expression.Interpret();
    std::cout << std::dec << value << std::endl;

    system("cmd /k");
    return EXIT_SUCCESS;
}
