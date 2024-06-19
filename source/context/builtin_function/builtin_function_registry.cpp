#include "context/builtin_function/builtin_function_registry.hpp"
#include "context/builtin_function/builtin_assert.hpp"
#include "context/builtin_function/builtin_file_functions.hpp"
#include "context/builtin_function/builtin_print.hpp"
#include "context/builtin_function/builtin_input.hpp"

#include "context/context.hpp"

void RegisterBuiltinFunctions(const FContext& context)
{
    // Register the print function
    {
        auto printFunction = CreatePrintFunction();
        context.AddSymbol(printFunction->GetFunctionDefinition()->GetFunctionName(), printFunction);
    }

    // Register the input function
    {
        auto inputFunction = CreateInputFunction();
        context.AddSymbol(inputFunction->GetFunctionDefinition()->GetFunctionName(), inputFunction);
    }

    // Register the open function
    {
        auto openFile = CreateOpenFileFunction();
        context.AddSymbol(openFile->GetFunctionDefinition()->GetFunctionName(), openFile);
    }
    
    // Register the read function
    {
        auto readFile = CreateReadFileFunction();
        context.AddSymbol(readFile->GetFunctionDefinition()->GetFunctionName(), readFile);
    }

    // Register the write function
    {
        auto writeFile = CreateWriteFileFunction();
        context.AddSymbol(writeFile->GetFunctionDefinition()->GetFunctionName(), writeFile);
    }
    
    // Register the close function
    {
        auto closeFile = CreateCloseFileFunction();
        context.AddSymbol(closeFile->GetFunctionDefinition()->GetFunctionName(), closeFile);
    }

    // Register the assert function
    {
        auto assertFunction = CreateAssertFunction();
        context.AddSymbol(assertFunction->GetFunctionDefinition()->GetFunctionName(), assertFunction);
    }
}
