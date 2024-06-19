#include "context/builtin_function/builtin_file_functions.hpp"

FBuiltinOpenFile::FBuiltinOpenFile(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinOpenFile::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    if (args.size() != 2)
    {
        throw std::runtime_error("open function requires exactly 2 arguments");
    }

    return {};
}

FBuiltinReadFile::FBuiltinReadFile(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinReadFile::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    if (args.size() != 1)
    {
        throw std::runtime_error("read function requires exactly 1 argument");
    }

    return {};
}

FBuiltinWriteFile::FBuiltinWriteFile(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinWriteFile::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    if (args.size() != 2)
    {
        throw std::runtime_error("write function expects two arguments");
    }

    return {};
}

FBuiltinCloseFile::FBuiltinCloseFile(
    FunctionDefinitionPtr functionDefinition)
    : CFunctionValue(functionDefinition)
{}

ValuePtr FBuiltinCloseFile::CallMethod(const FContext& context, const std::string& methodName, std::vector<ValuePtr> args) const
{
    if (args.size() != 1)
    {
        throw std::runtime_error("close function requires exactly 1 argument");
    }

    return {};
}

FunctionValuePtr CreateOpenFileFunction()
{
    std::string functionName = "open";
    FunctionParameters parameters = {  "string", "string" };
    std::string returnType = "string";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinOpenFile>(definition);
}

FunctionValuePtr CreateReadFileFunction()
{
    std::string functionName = "read";
    FunctionParameters parameters = { "string" };
    std::string returnType = "string";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinReadFile>(definition);
}

FunctionValuePtr CreateWriteFileFunction()
{
    std::string functionName = "write";
    FunctionParameters parameters = { "string", "string" };
    std::string returnType = "void";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinWriteFile>(definition);
}

FunctionValuePtr CreateCloseFileFunction()
{
    std::string functionName = "close";
    FunctionParameters parameters = { "string" };
    std::string returnType = "void";

    const auto& definition = std::make_shared<CFunctionDefinition>(
        functionName,
        parameters,
        returnType,
        nullptr
    );

    return std::make_shared<FBuiltinCloseFile>(definition);
}
