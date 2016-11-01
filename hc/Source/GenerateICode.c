#include "ParseNode.h"
#include "GenerateICode.h"
#include "Symbol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Variable* HasVariable(struct ParseNode* pn)
{
	if (pn->type == PNT_IDENTIFIER &&
		PSUB_PARSENODE(pn, struct IdentifierParseNode)->identifier &&
		PSUB_PARSENODE(pn, struct IdentifierParseNode)->identifier->type == ST_VARIABLE)
		return PSUB_SYMBOL(PSUB_PARSENODE(pn, struct IdentifierParseNode)->identifier, struct VariableSymbol)->variable;
	else if (pn->type == PNT_TEMP_VAR)
		return PSUB_PARSENODE(pn, struct TemporaryVariableParseNode)->variable;
	else if (pn->type == PNT_RETURNED_VAR)
		return PSUB_PARSENODE(pn, struct ReturnedVariableParseNode)->variable;

	return NULL;
}

const char* parseNodeTypeStrings[] =
{
	"PNT_IF",
	"PNT_WHILE",
	"PNT_FOR",
	"PNT_COMPOUND_STATEMENT",
	"PNT_EQUALITY",
	"PNT_ASSIGN",
	"PNT_ADD_ASSIGN",
	"PNT_SUB_ASSIGN",
	"PNT_MUL_ASSIGN",
	"PNT_DIV_ASSIGN",

	"PNT_ADD",
	"PNT_SUB",
	"PNT_MUL",
	"PNT_DIV",

	"PNT_GOTO",
	"PNT_CALL",
	"PNT_RET",
	"PNT_RET_VOID",

	"PNT_PRE_INCREMENT",
	"PNT_POST_INCREMENT",
	"PNT_PRE_DECREMENT",
	"PNT_POST_DECREMENT",

	"PNT_IDENTIFIER",
	"PNT_TEMP_VAR",
	"PNT_RETURNED_VAR",
	"PNT_CONST"
};

#define HANDLE_ASSIGN_PARSE_NODE(ICODE, VAR_TO_VAR_INS, VAR_TO_VAR_INS_TYPE, CONSTANT_TO_VAR_INS, CONSTANT_TO_VAR_INS_TYPE)\
	{\
		struct Variable* pn0v = HasVariable(pn0);\
		struct Variable* pn1v = HasVariable(pn1);\
		\
		rpn = pn0;\
		\
		if (pn1v)\
		{\
			VAR_TO_VAR_INS* i;\
			\
			ADD_INSTRUCTION(i, ICODE, VAR_TO_VAR_INS, VAR_TO_VAR_INS_TYPE);\
			i->dest = pn0v;\
			i->src = pn1v;\
		}\
		else\
		{\
			CONSTANT_TO_VAR_INS* i;\
			\
			ADD_INSTRUCTION(i, ICODE, CONSTANT_TO_VAR_INS, CONSTANT_TO_VAR_INS_TYPE);\
			i->dest = pn0v;\
			i->src = PSUB_PARSENODE(pn1, struct ConstParseNode)->value;\
		}\
	}

// We have a div/mul/add/sub expression (not assign)
// Ex: (3 + 4)
// 1. Create temporary variable
// 2. Create assign instruction (temp variable = first sub parse node arg*)
// 3. Create sub instruction (temp variable -= second sub parse node arg*)
// *Can be constant/variable- proper Instruction must be determined
#define HANDLE_TWO_ARG_PARSE_NODE(ICODE, VAR_TO_VAR_INS, VAR_TO_VAR_INS_TYPE, CONSTANT_TO_VAR_INS, CONSTANT_TO_VAR_INS_TYPE)\
	{\
		struct Variable* rpnv;\
		struct Variable* pn0v;\
		struct Variable* pn1v;\
		\
		PN_ALLOC(rpn, struct TemporaryVariableParseNode);\
		PN_SET_TYPE(rpn, PNT_TEMP_VAR);\
		PSUB_PARSENODE(rpn, struct TemporaryVariableParseNode)->variable = AddLocalTempVariable(VTS_INT32, f);\
		\
		rpnv = PSUB_PARSENODE(rpn, struct TemporaryVariableParseNode)->variable;\
		\
		pn0v = HasVariable(pn0);\
		pn1v = HasVariable(pn1);\
		\
		if (pn0v && pn1v)\
		{\
			struct AssignVarToVarIns* i0;\
			VAR_TO_VAR_INS* i1;\
			\
			ADD_INSTRUCTION(i0, (ICODE), struct AssignVarToVarIns, IT_ASSIGN_VAR_TO_VAR);\
			i0->dest = rpnv;\
			i0->src = pn0v;\
			\
			ADD_INSTRUCTION(i1, (ICODE), VAR_TO_VAR_INS, VAR_TO_VAR_INS_TYPE);\
			i1->dest = rpnv;\
			i1->src = pn1v;\
		}\
		else if (pn0->type == PNT_CONST && pn1->type == PNT_CONST)\
		{\
			struct AssignConstantToVarIns* i0;\
			CONSTANT_TO_VAR_INS* i1;\
			\
			ADD_INSTRUCTION(i0, (ICODE), struct AssignConstantToVarIns, IT_ASSIGN_CONSTANT_TO_VAR);\
			i0->dest = rpnv;\
			i0->src = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0, struct ConstParseNode)->value;\
			i0->src.type = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0, struct ConstParseNode)->value.type;\
			\
			ADD_INSTRUCTION(i1, (ICODE), CONSTANT_TO_VAR_INS, CONSTANT_TO_VAR_INS_TYPE);\
			i1->dest = rpnv;\
			i1->src  = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, struct ConstParseNode)->value;\
			i1->src.type = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, struct ConstParseNode)->value.type;\
		}\
		else if (pn0v && pn1->type == PNT_CONST)\
		{\
			struct AssignVarToVarIns* i0;\
			CONSTANT_TO_VAR_INS* i1;\
			\
			ADD_INSTRUCTION(i0, (ICODE), struct AssignVarToVarIns, IT_ASSIGN_VAR_TO_VAR);\
			i0->dest = rpnv;\
			i0->src = pn0v;\
			\
			ADD_INSTRUCTION(i1, (ICODE), CONSTANT_TO_VAR_INS, CONSTANT_TO_VAR_INS_TYPE);\
			i1->dest = rpnv;\
			i1->src = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, struct ConstParseNode)->value;\
			i1->src.type = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, struct ConstParseNode)->value.type;\
		}\
		else if (pn0->type == PNT_CONST && pn1v)\
		{\
			struct AssignConstantToVarIns* i0;\
			VAR_TO_VAR_INS* i1;\
			\
			ADD_INSTRUCTION(i0, (ICODE), struct AssignConstantToVarIns, IT_ASSIGN_CONSTANT_TO_VAR);\
			i0->dest = rpnv;\
			i0->src = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0, struct ConstParseNode)->value;\
			i0->src.type = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0, struct ConstParseNode)->value.type;\
			\
			ADD_INSTRUCTION(i1, (ICODE), VAR_TO_VAR_INS, VAR_TO_VAR_INS_TYPE);\
			i1->dest = rpnv;\
			i1->src = pn1v;\
		}\
		else\
		{\
			ASSERT(0);\
		}\
	}

static struct ParseNode* GenerateICodeR(struct ParseNode* pn, struct Function* f)
{
	// Variable from arg0
	struct ParseNode* pn0 = NULL;

	// Variable from arg1 (if exists)
	struct ParseNode* pn1 = NULL;

	// Returned variable
	struct ParseNode* rpn = NULL;

	// Preorder traversal
	switch (pn->type)
	{
	case PNT_ASSIGN:
	case PNT_ADD_ASSIGN:
	case PNT_SUB_ASSIGN:
	case PNT_MUL_ASSIGN:
	case PNT_DIV_ASSIGN:
	case PNT_DIV:
	case PNT_MUL:
	case PNT_ADD:
	case PNT_SUB:
		pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0, f);
		pn1 = GenerateICodeR(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, f);
		break;

	case PNT_IF:
		{
			struct CmpVarAndConstant* i0;
			struct JmpCondition* i1;

			pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct IfParseNode)->conditionalExpression, f);

			ADD_INSTRUCTION(i0, f->intermediateCodeEnd, struct CmpVarAndConstant, IT_CMP_VAR_AND_CONSTANT);
			i0->arg0 = HasVariable(pn0);
			i0->arg1 = zero32BitConstant;

			ADD_INSTRUCTION(i1, f->intermediateCodeEnd, struct JmpCondition, IT_JMP_CONDITION);
			i1->condition = CC_E;

			pn1 = GenerateICodeR(PSUB_PARSENODE(pn, struct IfParseNode)->bodyCompoundStatement, f);

			i1->dest = f->intermediateCodeEnd;
			break;
		}

	case PNT_WHILE:
		{
			struct CmpVarAndConstant* i0;
			struct JmpCondition* i1;
			struct Jmp* i2;
			struct Instruction* i2Dest;

			i2Dest = f->intermediateCodeEnd;

			pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct WhileParseNode)->conditionalExpression, f);

			ADD_INSTRUCTION(i0, f->intermediateCodeEnd, struct CmpVarAndConstant, IT_CMP_VAR_AND_CONSTANT);
			i0->arg0 = HasVariable(pn0);
			i0->arg1 = zero32BitConstant;

			ADD_INSTRUCTION(i1, f->intermediateCodeEnd, struct JmpCondition, IT_JMP_CONDITION);
			i1->condition = CC_E;

			pn1 = GenerateICodeR(PSUB_PARSENODE(pn, struct WhileParseNode)->bodyCompoundStatement, f);

			ADD_INSTRUCTION(i2, f->intermediateCodeEnd, struct Jmp, IT_JMP);
			i2->dest = i2Dest;
			
			i1->dest = f->intermediateCodeEnd;
			break;
		}

	case PNT_FOR:
		{

			// /* Init statement */
			// 
			// StartLoop:
			// 
			// cmp /* Conditional Expression */, 0
			// je End
			// 
			// /* Body */
			// 
			// /* Count Statement */
			// jmp StartLoop
			// 
			// End:
			// nop

			struct CmpVarAndConstant* i0;
			struct JmpCondition* i1;
			struct Jmp* i2;
			struct Instruction* i2Dest;

			GenerateICodeR(PSUB_PARSENODE(pn, struct ForParseNode)->initStatement, f);

			i2Dest = f->intermediateCodeEnd;

			pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct ForParseNode)->conditionalExpression, f);

			ADD_INSTRUCTION(i0, f->intermediateCodeEnd, struct CmpVarAndConstant, IT_CMP_VAR_AND_CONSTANT);
			i0->arg0 = HasVariable(pn0);
			i0->arg1 = zero32BitConstant;

			ADD_INSTRUCTION(i1, f->intermediateCodeEnd, struct JmpCondition, IT_JMP_CONDITION);
			i1->condition = CC_E;

			pn1 = GenerateICodeR(PSUB_PARSENODE(pn, struct ForParseNode)->bodyCompoundStatement, f);

			GenerateICodeR(PSUB_PARSENODE(pn, struct ForParseNode)->countingStatement, f);

			ADD_INSTRUCTION(i2, f->intermediateCodeEnd, struct Jmp, IT_JMP);
			i2->dest = i2Dest;
			
			i1->dest = f->intermediateCodeEnd;
			break;
		}

	case PNT_EQUALITY:
		pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct EqualityParseNode)->arg0, f);
		pn1 = GenerateICodeR(PSUB_PARSENODE(pn, struct EqualityParseNode)->arg1, f);
		break;

	case PNT_GOTO:
	case PNT_PRE_INCREMENT:
	case PNT_POST_INCREMENT:
	case PNT_PRE_DECREMENT:
	case PNT_POST_DECREMENT:
		pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct OneArgParseNode)->arg0, f);
		break;

	case PNT_RET:
		pn0 = GenerateICodeR(PSUB_PARSENODE(pn, struct ReturnParseNode)->returnValue, f);
		break;

    case PNT_CALL:
		{
			struct ParseNode** p;
			for (p = PSUB_PARSENODE(pn, struct CallParseNode)->parametersStart; p < PSUB_PARSENODE(pn, struct CallParseNode)->parametersEnd; ++p)
			{
				*p = GenerateICodeR(*p, f);
			}
			//pn1 = GenerateICodeR(PSUB_PARSENODE(pn, struct CallParseNode)-, f);
			break;
		}
	case PNT_TEMP_VAR:
	case PNT_IDENTIFIER:
	case PNT_CONST:
		break;

	case PNT_COMPOUND_STATEMENT:
		{
			struct ParseNode** stmts;

			for (stmts = PSUB_PARSENODE(pn, struct CompoundStatementParseNode)->statements; *stmts; ++stmts)
				GenerateICodeR(*stmts, f);
			
			rpn = (struct ParseNode*)f->intermediateCodeEnd;
			break;
		}
	}
	
	printf("%s\n", parseNodeTypeStrings[pn->type]);

	switch (pn->type)
	{
	case PNT_ASSIGN:
		{
			if (pn0)
			{
				struct Variable* pn0v;
				struct Variable* pn1v;
				
				pn0v = HasVariable(pn0);

				ASSERT(pn0v);

				if ((pn1v = HasVariable(pn1)))
				{
					struct AssignVarToVarIns* i0;

					ADD_INSTRUCTION(i0, f->intermediateCodeEnd, struct AssignVarToVarIns, IT_ASSIGN_VAR_TO_VAR);
					i0->dest = pn0v;
					i0->src = pn1v;
				}
				else
				{
					struct AssignConstantToVarIns* i0;

					ADD_INSTRUCTION(i0, f->intermediateCodeEnd, struct AssignConstantToVarIns, IT_ASSIGN_CONSTANT_TO_VAR);
					i0->dest = pn0v;
					i0->src = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, struct ConstParseNode)->value;
					i0->src.type = PSUB_PARSENODE(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1, struct ConstParseNode)->value.type;
				}

				rpn = pn0;
			}
			break;
		}
	case PNT_ADD_ASSIGN:
		HANDLE_ASSIGN_PARSE_NODE(f->intermediateCodeEnd, struct AddVarToVarIns, IT_ADD_VAR_TO_VAR, struct AddConstantToVarIns, IT_ADD_CONSTANT_TO_VAR);
		break;

	case PNT_SUB_ASSIGN:
		HANDLE_ASSIGN_PARSE_NODE(f->intermediateCodeEnd, struct SubVarFromVarIns, IT_SUB_VAR_FROM_VAR, struct SubConstantFromVarIns, IT_SUB_CONSTANT_FROM_VAR);
		break;

	case PNT_MUL_ASSIGN:
		HANDLE_ASSIGN_PARSE_NODE(f->intermediateCodeEnd, struct MulVarByVarIns, IT_MUL_VAR_BY_VAR, struct MulVarByConstantIns, IT_MUL_VAR_BY_CONSTANT);
		break;

	case PNT_DIV_ASSIGN:
		HANDLE_ASSIGN_PARSE_NODE(f->intermediateCodeEnd, struct DivVarByVarIns, IT_DIV_VAR_BY_VAR, struct DivVarByConstantIns, IT_DIV_VAR_BY_CONSTANT);
		break;

	case PNT_DIV:
		HANDLE_TWO_ARG_PARSE_NODE(f->intermediateCodeEnd, struct DivVarByVarIns, IT_DIV_VAR_BY_VAR, struct DivVarByConstantIns, IT_DIV_VAR_BY_CONSTANT);
		break;

	case PNT_MUL:
		HANDLE_TWO_ARG_PARSE_NODE(f->intermediateCodeEnd, struct MulVarByVarIns, IT_MUL_VAR_BY_VAR, struct MulVarByConstantIns, IT_MUL_VAR_BY_CONSTANT);
		break;

	case PNT_ADD:
		HANDLE_TWO_ARG_PARSE_NODE(f->intermediateCodeEnd, struct AddVarToVarIns, IT_ADD_VAR_TO_VAR, struct AddConstantToVarIns, IT_ADD_CONSTANT_TO_VAR);
		break;

	case PNT_SUB:
		HANDLE_TWO_ARG_PARSE_NODE(f->intermediateCodeEnd, struct SubVarFromVarIns, IT_SUB_VAR_FROM_VAR, struct SubConstantFromVarIns, IT_SUB_CONSTANT_FROM_VAR);
		break;

	case PNT_GOTO:
		break;

	case PNT_IF:
		break;

	case PNT_EQUALITY:
		{
			struct Variable* rpnv;
			struct Variable* pn0v;
			struct Variable* pn1v;
			struct SetCondition* sc;

			PN_ALLOC(rpn, struct TemporaryVariableParseNode);
			PN_SET_TYPE(rpn, PNT_TEMP_VAR);
			PSUB_PARSENODE(rpn, struct TemporaryVariableParseNode)->variable = rpnv = AddLocalTempVariable(VTS_UINT32, f);

			pn0v = HasVariable(pn0);
			pn1v = HasVariable(pn1);

			if (pn0v && pn1v)
			{
				struct CmpVarAndVar* i;

				ADD_INSTRUCTION(i, f->intermediateCodeEnd, struct CmpVarAndVar, IT_CMP_VAR_AND_VAR);
				i->arg0 = pn0v;
				i->arg1 = pn1v;
			}
			else if (pn0->type == PNT_CONST && pn1->type == PNT_CONST)
			{
				struct CmpConstantAndConstant* i;

				ADD_INSTRUCTION(i, f->intermediateCodeEnd, struct CmpConstantAndConstant, IT_CMP_CONSTANT_AND_CONSTANT);
				i->arg0 = PSUB_PARSENODE(pn0, struct ConstParseNode)->value;
				i->arg1 = PSUB_PARSENODE(pn1, struct ConstParseNode)->value;
			}
			else if (pn0v && pn1->type == PNT_CONST)
			{
				struct CmpVarAndConstant* i;

				ADD_INSTRUCTION(i, f->intermediateCodeEnd, struct CmpVarAndConstant, IT_CMP_VAR_AND_CONSTANT);
				i->arg0 = pn0v;
				i->arg1 = PSUB_PARSENODE(pn1, struct ConstParseNode)->value;
			}
			else if (pn0->type == PNT_CONST && pn1v)
			{
				struct CmpVarAndConstant* i;

				ADD_INSTRUCTION(i, f->intermediateCodeEnd, struct CmpVarAndConstant, IT_CMP_VAR_AND_CONSTANT);
				i->arg0 = pn1v;
				i->arg1 = PSUB_PARSENODE(pn0, struct ConstParseNode)->value;
			}

			ADD_INSTRUCTION(sc, f->intermediateCodeEnd, struct SetCondition, IT_SET_CONDITION);
			sc->condition = (enum CONDITION_CODE)PSUB_PARSENODE(pn, struct EqualityParseNode)->eqType;

			PN_ALLOC(rpn, struct TemporaryVariableParseNode);
			PN_SET_TYPE(rpn, PNT_TEMP_VAR);
			sc->dest = PSUB_PARSENODE(rpn, struct TemporaryVariableParseNode)->variable = AddLocalTempVariable(VTS_UINT32, f);
		}
		break;

	case PNT_PRE_INCREMENT:
	case PNT_POST_INCREMENT:
	case PNT_PRE_DECREMENT:
	case PNT_POST_DECREMENT:
		return PSUB_PARSENODE(pn, struct OneArgParseNode)->arg0;
		break;

	case PNT_IDENTIFIER:
	case PNT_CONST:
	case PNT_TEMP_VAR:
		rpn = pn;
		break;

	case PNT_CALL:
		{
			struct AssignVarToVarIns* i0;
			struct CallIns* callIns;
			struct CallParseNode* callParseNode = PSUB_PARSENODE(pn, struct CallParseNode);
			UInt numParameters = callParseNode->parametersEnd - callParseNode->parametersStart;

			if (!callParseNode->function->identifier &&
				!(callParseNode->function->identifier = FindFunctionSymbolByName(callParseNode->function->name)))
				COMPILER_ERRORF("Function %s does not exist.", callParseNode->function->name);

			ADD_INSTRUCTION(callIns, f->intermediateCodeEnd, struct CallIns, IT_CALL);
			callIns->function = callParseNode->function->identifier;
			memcpy(callIns->parametersStart, callParseNode->parametersStart, numParameters * sizeof(struct ParseNode*));
			callIns->parametersEnd = callIns->parametersStart + numParameters;

			// Move function return value to variable
			ADD_INSTRUCTION(i0, f->intermediateCodeEnd, struct AssignVarToVarIns, IT_ASSIGN_VAR_TO_VAR);
			f->localVariablesEnd->stackOffset = MAX_INT;
			f->localVariablesEnd->type = PSUB_SYMBOL(callIns->function, struct FunctionSymbol)->function->returnType;
			i0->src = f->localVariablesEnd;
			ADD_BYTES_TO_P(f->localVariablesEnd, struct Variable*, sizeof(struct Variable));

			PN_ALLOC(rpn, struct TemporaryVariableParseNode);
			PN_SET_TYPE(rpn, PNT_TEMP_VAR);
			i0->dest = PSUB_PARSENODE(rpn, struct TemporaryVariableParseNode)->variable = AddLocalTempVariable(i0->src->type.specifier, f);
		}
		break;

	case PNT_RET_VOID:
		{
			f->intermediateCodeEnd->type = IT_RETURN_VOID;
			++f->intermediateCodeEnd;
		}
		break;
	case PNT_RET:
		{
			struct IdentifierParseNode* ipn = PSUB_PARSENODE(pn0, struct IdentifierParseNode);
			struct Variable* pn0v = HasVariable(pn0);

			if (pn0v)
			{
				struct ReturnVar* retIns;
				ADD_INSTRUCTION(retIns, f->intermediateCodeEnd, struct ReturnVar, IT_RETURN_VAR);
				retIns->returnValue = pn0v;
			}
			else
			{
				struct ReturnConstant* retIns;
				ADD_INSTRUCTION(retIns, f->intermediateCodeEnd, struct ReturnConstant, IT_RETURN_CONSTANT);
				retIns->returnValue = PSUB_PARSENODE(pn0, struct ConstParseNode)->value;
			}
		}
		break;
	}

	return rpn;
}

void GenerateICode(struct FunctionTable* ft, struct SymbolTable* gst)
{
	{
		struct Function** f;
		for (f = ft->functions; *f; ++f)
		{
			struct ParseNode** stmts;
			
			for (stmts = (*f)->body->statements; *stmts; ++stmts)
            {
				GenerateICodeR(*stmts, *f);
				printf("Finished statement\n");
            }

			printf("Finished function\n");
		}
	}
}
