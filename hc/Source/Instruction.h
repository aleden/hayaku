#pragma once
#include "Common.h"
#include "Function.h"

enum INSTRUCTION_TYPE
{
	IT_ASSIGN_VAR_TO_VAR,
	IT_ASSIGN_CONSTANT_TO_VAR,

	IT_ADD_VAR_TO_VAR,
	IT_ADD_CONSTANT_TO_VAR,

	IT_SUB_VAR_FROM_VAR,
	IT_SUB_CONSTANT_FROM_VAR,

	IT_MUL_VAR_BY_VAR,
	IT_MUL_VAR_BY_CONSTANT,

	IT_DIV_VAR_BY_VAR,
	IT_DIV_VAR_BY_CONSTANT,

	IT_RETURN_VOID,
	IT_RETURN_CONSTANT,
	IT_RETURN_VAR,

	IT_CMP_VAR_AND_VAR,
	IT_CMP_VAR_AND_CONSTANT,
	IT_CMP_CONSTANT_AND_CONSTANT,
	IT_SET_CONDITION,
	IT_JMP,
	IT_JMP_CONDITION,

	IT_CALL
};

struct Instruction
{
	enum INSTRUCTION_TYPE type;
};

struct ReturnConstant
{
	struct Constant returnValue;
};

struct ReturnVar
{
	struct Variable* returnValue;
};

struct VarToVarIns
{
	struct Variable* src;
	struct Variable* dest;
};

struct CallIns
{
	struct Symbol* function;
	struct ParseNode* parametersStart[FUNCTION_PARAMETERS_SIZE];
	struct ParseNode** parametersEnd;
};

struct ConstantToVarIns
{
	struct Variable* dest;
	struct Constant src;
};

enum CONDITION_CODE
{
	CC_E,
	CC_NE,
	CC_G,
	CC_GE,
	CC_L,
	CC_LE,
	CC_Z,
	CC_NZ
};

// Sets destination to 1 if the condition flag is true
struct SetCondition
{
	enum CONDITION_CODE condition;
	struct Variable* dest;
};

struct JmpCondition
{
	enum CONDITION_CODE condition;
	struct Instruction* dest;
};

struct Jmp
{
	struct Instruction* dest;
};

struct CmpVarAndVar
{
	struct Variable* arg0;
	struct Variable* arg1;
};

struct CmpVarAndConstant
{
	struct Variable* arg0;
	struct Constant arg1;
};

struct CmpConstantAndConstant
{
	struct Constant arg0;
	struct Constant arg1;
};

#define AssignVarToVarIns VarToVarIns
#define AddVarToVarIns VarToVarIns
#define SubVarFromVarIns VarToVarIns
#define MulVarByVarIns VarToVarIns
#define DivVarByVarIns VarToVarIns

#define AssignConstantToVarIns ConstantToVarIns
#define AddConstantToVarIns ConstantToVarIns
#define SubConstantFromVarIns ConstantToVarIns
#define MulVarByConstantIns ConstantToVarIns
#define DivVarByConstantIns ConstantToVarIns


static const UInt instructionSizes[] = 
{
	sizeof(struct AssignVarToVarIns), // IT_ASSIGN_VAR_TO_VAR,
	sizeof(struct AssignConstantToVarIns), // IT_ASSIGN_CONSTANT_TO_VAR,

	sizeof(struct AddVarToVarIns), // IT_ADD_VAR_TO_VAR,
	sizeof(struct AddConstantToVarIns), // IT_ADD_CONSTANT_TO_VAR,

	sizeof(struct SubVarFromVarIns), // IT_SUB_VAR_FROM_VAR,
	sizeof(struct SubConstantFromVarIns), // IT_SUB_CONSTANT_FROM_VAR,

	sizeof(struct MulVarByVarIns), // IT_MUL_VAR_BY_VAR,
	sizeof(struct MulVarByConstantIns), // IT_MUL_VAR_BY_CONSTANT,

	sizeof(struct DivVarByVarIns), // IT_DIV_VAR_BY_VAR,
	sizeof(struct DivVarByConstantIns), // IT_DIV_VAR_BY_CONSTANT,

	0, // IT_RETURN_VOID,
	sizeof(struct ReturnConstant), // IT_RETURN_CONSTANT,
	sizeof(struct ReturnVar), // IT_RETURN_VAR,

	sizeof(struct CmpVarAndVar), // IT_CMP_VAR_AND_VAR,
	sizeof(struct CmpVarAndConstant), // IT_CMP_VAR_AND_CONSTANT,
	sizeof(struct CmpConstantAndConstant), // IT_CMP_CONSTANT_AND_CONSTANT,
	sizeof(struct SetCondition), // IT_SET_CONDITION,
	sizeof(struct Jmp), // IT_JMP,
	sizeof(struct JmpCondition), // IT_JMP_CONDITION,

	sizeof(struct CallIns), // IT_CALL
};

#define ADD_INSTRUCTION(DEST, ICODE, INSTRUCTION_STRUCT, INSTRUCTION_TYPE)\
	DEST = PSUB_INSTRUCTION((ICODE), INSTRUCTION_STRUCT);\
	((struct Instruction*)(ICODE))->type = INSTRUCTION_TYPE;\
	ICODE = ((struct Instruction*)(((Int8*)(ICODE)) + (sizeof(INSTRUCTION_STRUCT) + sizeof(struct Instruction))));

#define PSUB_INSTRUCTION(I, SUB) ((SUB*)(((Int8*)(I)) + sizeof(struct Instruction)))