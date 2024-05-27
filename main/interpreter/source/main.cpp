#include <iostream>
#include "interpreter.hpp"

int main(const int argc, const char* argv[])
{
	std::vector<std::string> keywords = { "var", "print" };
	FInterpreter interpreter(argc, argv, keywords);

	try {
		interpreter.Interpret();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
