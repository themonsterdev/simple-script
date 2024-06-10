#pragma once

#include "function/function_definition.hpp"
#include <fstream>

class FBuiltinOpenFile final : public CFunctionDefinition
{
public:

    FBuiltinOpenFile(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const;
};

class FBuiltinReadFile final : public CFunctionDefinition
{
public:

    FBuiltinReadFile(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const;
};

class FBuiltinWriteFile final : public CFunctionDefinition
{
public:

    FBuiltinWriteFile(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const;
};

class FBuiltinCloseFile final : public CFunctionDefinition
{
public:

    FBuiltinCloseFile(
        const std::string& name,
        TypePtr returnType,
        FunctionParameters parameters
    );

    ValuePtr Invoke(const FContext& context, const std::vector<ValuePtr>& arguments) const override;
};

FunctionDefinitionPtr CreateOpenFileFunction();
FunctionDefinitionPtr CreateReadFileFunction();
FunctionDefinitionPtr CreateWriteFileFunction();
FunctionDefinitionPtr CreateCloseFileFunction();
