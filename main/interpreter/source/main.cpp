#include <iostream>
#include <fstream>

#include "tokenizer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

int main(const int argc, const char* args[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: interpreter.exe" << " <script_file>" << std::endl;
		return EXIT_FAILURE;
	}

	const char* scriptFile = args[1];

	// Lecture du contenu du fichier de script
	std::ifstream file(scriptFile);
	if (!file.is_open())
	{
		std::cerr << "Error: Failed to open script file." << std::endl;
		return EXIT_FAILURE;
	}

	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	std::vector<std::string> keywords = { "var", "print" };

	FTokenizer tokenizer(input, keywords);
	FParser parser(tokenizer);

	try {
		std::unique_ptr<FSyntaxTree> tree = parser.Parse();

		FInterpreter interpreter;
		interpreter.Interpret(tree.release());
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}
