#include "builtin_function/builtin_function_registry.hpp"
#include "builtin_function/builtin_assert.hpp"
#include "builtin_function/builtin_file_functions.hpp"
#include "builtin_function/builtin_print.hpp"
#include "builtin_function/builtin_input.hpp"

#include "context.hpp"

void RegisterBuiltinFunctions(const FContext& context)
{
    // Register the print function
    {
        auto printFunction = CreatePrintFunction();
        context.RegisterFunction("print", printFunction);
    }

    // Register the input function
    {
        auto inputFunction = CreateInputFunction();
        context.RegisterFunction("input", inputFunction);
    }

    // Register the open function
    {
        auto openFile = CreateOpenFileFunction();
        context.RegisterFunction("open", openFile);
    }
    
    // Register the read function
    {
        auto readFile = CreateReadFileFunction();
        context.RegisterFunction("read", readFile);
    }

    // Register the write function
    {
        auto writeFile = CreateWriteFileFunction();
        context.RegisterFunction("write", writeFile);
    }
    
    // Register the close function
    {
        auto closeFile = CreateCloseFileFunction();
        context.RegisterFunction("close", closeFile);
    }

    // Register the assert function
    {
        auto assertFunction = CreateAssertFunction();
        context.RegisterFunction("assert", assertFunction);
    }
}
