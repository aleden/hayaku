#pragma once
#include "Common.h"
#include "Variable.h"
#include "Symbol.h"

#define FUNCTION_PARAMETERS_SIZE 0x10
#define FUNCTION_STATEMENTS_DATA_SIZE 0x1000
#define FUNCTION_PARSE_TREE_DATA_SIZE 0x1000
#define FUNCTION_LOCAL_VARIABLES_DATA_SIZE 0x100
#define FUNCTION_INTERMEDIATE_CODE_DATA_SIZE 0x10000
#define FUNCTION_INTERMEDIATE_MACHINE_CODE_DATA_SIZE 0x10000
#define FUNCTION_MACHINE_CODE_DATA_SIZE 0x10000
#define FUNCTION_BACK_PATCHES_DATA_SIZE 0x1000
#define FUNCTION_EXTRA_DATA_SIZE 0x1000

typedef void (*BackPatcher)(struct BackPatch*);

struct BackPatch
{
	BackPatcher patcher;

	struct
	{
		UInt size;
		void* pointer;
	} src;

	struct
	{
		UInt opCode;
		// From end of operation
		UInt byteOffset;
	} preDest;

	struct
	{
		UInt size;
		void* pointer;
	} dest;

	UInt extra;
};

void GenericBackPatcher(struct BackPatch* patch);

struct Function
{
	struct VariableType parametersStart[FUNCTION_PARAMETERS_SIZE];
	struct VariableType* parametersEnd;
	UInt sizeOfParameters;

	struct VariableType returnType;

	struct SymbolTable symbolTable;

	struct CompoundStatementParseNode* body;

	UInt8 parseTreeStart[FUNCTION_PARSE_TREE_DATA_SIZE];
	struct ParseNode* parseTreeEnd;

	UInt8 localVariablesStart[FUNCTION_LOCAL_VARIABLES_DATA_SIZE];
	struct Variable* localVariablesEnd;

	UInt localVariablesAlloc;
	UInt parameterVariablesAlloc;

	UInt8 intermediateCodeStart[FUNCTION_INTERMEDIATE_CODE_DATA_SIZE];
	struct Instruction* intermediateCodeEnd;

	UInt8 intermediateMachineCodeStart[FUNCTION_MACHINE_CODE_DATA_SIZE];
	UInt8* intermediateMachineCodeEnd;

	UInt8 machineCodeStart[FUNCTION_MACHINE_CODE_DATA_SIZE];
	UInt8* machineCodeEnd;

	UInt8 backPatchesStart[FUNCTION_BACK_PATCHES_DATA_SIZE];
	struct BackPatch* backPatchesEnd;

	UInt codeStart;

	UInt8 extraDataStart[FUNCTION_EXTRA_DATA_SIZE];
	UInt8* extraDataEnd;

	const char* name;
};

void AddGenericBackPatch(struct Function* f,
                  void* srcPointer,
                  UInt srcSize,
                  UInt pdOpCode,
                  UInt pdByteOffset,
                  UInt destSize);

void InitializeFunction(struct Function* f);

#define FUNCTION_TABLE_FUNCTIONS_SIZE 0x10

struct FunctionTable
{
	struct Function* functions[FUNCTION_TABLE_FUNCTIONS_SIZE];
	UInt numFunctions;
};

void InitializeFunctionTable(struct FunctionTable* ft);

#define ADD_FUNCTION(GLOBAL_SYMBOL_TABLE, FUNCTION_TABLE, NAME)\
	FUNCTION_TABLE->functions[FUNCTION_TABLE->numFunctions] = (struct Function*)malloc(sizeof(struct Function));\
	InitializeFunction(FUNCTION_TABLE->functions[FUNCTION_TABLE->numFunctions]);\
	AddFunctionSymbol(GLOBAL_SYMBOL_TABLE, NAME, FUNCTION_TABLE->functions[FUNCTION_TABLE->numFunctions]);\
	++FUNCTION_TABLE->numFunctions;

#define ALLOC_FUNCTION(FUNCTION_TABLE)\
	FUNCTION_TABLE->functions[FUNCTION_TABLE->numFunctions] = (struct Function*)malloc(sizeof(struct Function));\
	InitializeFunction(FUNCTION_TABLE->functions[FUNCTION_TABLE->numFunctions])
