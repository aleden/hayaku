#pragma once
#include "Common.h"

// Value of enums equal to size in bytes
enum VARIABLE_TYPE_SPECIFIER
{
	VTS_INT,
	VTS_INT8,
	VTS_INT16,
	VTS_INT32,
	VTS_INT64,

	VTS_UINT,
	VTS_UINT8,
	VTS_UINT16,
	VTS_UINT32,
	VTS_UINT64,

	VTS_FLOAT,
	VTS_FLOAT32,
	VTS_FLOAT64,

	VTS_BITS8,
	VTS_BITS16,
	VTS_BITS32,
	VTS_BITS64,

	VTS_VOID,
	VTS_FUNCTION_POINTER
	// All values beyond are pointers to symbolsEnd (typedefs/classes)
};

struct VariableType
{
	enum VARIABLE_TYPE_SPECIFIER specifier;
	UInt pointerDegree;
};

static const UInt variableTypeSizes[] = {4, 1, 2, 4, 8, 4, 1, 2, 4, 8, 4, 8, 1, 2, 4, 8};

enum VARIABLE_MODIFIER
{
	VM_CONST
};

struct Variable
{
	struct VariableType type;
	
	// if MAX_INT, then is return value
	Int stackOffset;
};

#define PSUB_VARIABLE(V, SUB_STRUCT)\
	((SUB_STRUCT*)(((Int8*)(V)) + sizeof(struct Variable)))

#define AddLocalTempVariable(VARIABLE_TYPE_SPECIFIER, FUNCTION)\
	AddLocalVariable(VARIABLE_TYPE_SPECIFIER, 0, FUNCTION)

#define AddLocalVariable(VARIABLE_TYPE_SPECIFIER, VARIABLE_TYPE_POINTER_DEGREE, FUNCTION)\
	FUNCTION->localVariablesEnd;\
	((struct Variable*)FUNCTION->localVariablesEnd)->stackOffset = (-(Int)(FUNCTION->localVariablesAlloc)) - 4;\
	FUNCTION->localVariablesAlloc += variableTypeSizes[0];\
	((struct Variable*)FUNCTION->localVariablesEnd)->type.specifier = VARIABLE_TYPE_SPECIFIER;\
	((struct Variable*)FUNCTION->localVariablesEnd)->type.pointerDegree = VARIABLE_TYPE_POINTER_DEGREE;\
	ADD_BYTES_TO_P(FUNCTION->localVariablesEnd, struct Variable*, sizeof(struct Variable))

#define AddLocalParameter(VARIABLE_TYPE_SPECIFIER, VARIABLE_TYPE_POINTER_DEGREE, FUNCTION)\
	FUNCTION->localVariablesEnd;\
	((struct Variable*)FUNCTION->localVariablesEnd)->stackOffset = FUNCTION->parameterVariablesAlloc + 8;\
	FUNCTION->parameterVariablesAlloc += variableTypeSizes[0];\
	((struct Variable*)FUNCTION->localVariablesEnd)->type.specifier = VARIABLE_TYPE_SPECIFIER;\
	((struct Variable*)FUNCTION->localVariablesEnd)->type.pointerDegree = VARIABLE_TYPE_POINTER_DEGREE;\
	ADD_BYTES_TO_P(FUNCTION->localVariablesEnd, struct Variable*, sizeof(struct Variable))
