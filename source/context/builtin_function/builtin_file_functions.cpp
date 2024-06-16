#include "context/builtin_function/builtin_file_functions.hpp"

FBuiltinOpenFile::FBuiltinOpenFile(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinOpenFile::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    if (arguments.size() != 2)
    {
        throw std::runtime_error("open function requires exactly 2 arguments");
    }

    return {};
}

FBuiltinReadFile::FBuiltinReadFile(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinReadFile::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    if (arguments.size() != 1)
    {
        throw std::runtime_error("read function requires exactly 1 argument");
    }

    return {};
}

FBuiltinWriteFile::FBuiltinWriteFile(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinWriteFile::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    if (arguments.size() != 2)
    {
        throw std::runtime_error("write function expects two arguments");
    }

    return {};
}

FBuiltinCloseFile::FBuiltinCloseFile(
    const std::string& name,
    TypePtr returnType,
    FunctionParameters parameters)
    : CFunctionDefinition(name, returnType, parameters, nullptr)
{}

ValuePtr FBuiltinCloseFile::Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const
{
    if (arguments.size() != 1)
    {
        throw std::runtime_error("close function requires exactly 1 argument");
    }

    return {};
}

FunctionDefinitionPtr CreateOpenFileFunction()
{
    std::string name = "open";
    TypePtr returnType = std::make_shared<FType>(eTypeKind::STRING);

    FunctionParameters parameters = {
        { "string", "string" },
        { "string", "string" }
    };

    return std::make_shared<FBuiltinOpenFile>(
        name,
        returnType,
        parameters
    );
}

FunctionDefinitionPtr CreateReadFileFunction()
{
    std::string name = "read";
    TypePtr returnType = std::make_shared<FType>(eTypeKind::STRING);

    FunctionParameters parameters = {
        { "string", "string" }
    };

    return std::make_shared<FBuiltinReadFile>(
        name,
        returnType,
        parameters
    );
}

FunctionDefinitionPtr CreateWriteFileFunction()
{
    std::string name = "write";
    TypePtr returnType = std::make_shared<FType>(eTypeKind::VOID);

    FunctionParameters parameters = {
        { "string", "string" },
        { "string", "string" }
    };

    return std::make_shared<FBuiltinWriteFile>(
        name,
        returnType,
        parameters
    );
}

FunctionDefinitionPtr CreateCloseFileFunction()
{
    std::string name = "close";
    TypePtr returnType = std::make_shared<FType>(eTypeKind::VOID);

    FunctionParameters parameters = {
        { "string", "string" },
    };

    return std::make_shared<FBuiltinCloseFile>(
        name,
        returnType,
        parameters
    );
}
