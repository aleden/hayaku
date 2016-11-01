#pragma once
#include "Common.h"
#include "ICode.h"

enum PARSE_NODE_TYPE
{
	PNT_IF,
	PNT_WHILE,
	PNT_FOR,
	PNT_COMPOUND_STATEMENT,
	PNT_EQUALITY,
	PNT_ASSIGN,
	PNT_ADD_ASSIGN,
	PNT_SUB_ASSIGN,
	PNT_MUL_ASSIGN,
	PNT_DIV_ASSIGN,

	PNT_ADD,
	PNT_SUB,
	PNT_MUL,
	PNT_DIV,

	PNT_GOTO,
	PNT_CALL,
	PNT_RET,
	PNT_RET_VOID,
	
	PNT_PRE_INCREMENT,
	PNT_POST_INCREMENT,
	PNT_PRE_DECREMENT,
	PNT_POST_DECREMENT,

	PNT_IDENTIFIER,
	PNT_TEMP_VAR,
	PNT_RETURNED_VAR,
	PNT_CONST
};

struct ParseNode
{
	enum PARSE_NODE_TYPE type;
};

// Sub classes of ParseNode

struct OneArgParseNode
{
	struct ParseNode* arg0;
};

struct TwoArgParseNode
{
	struct ParseNode* arg0;
	struct ParseNode* arg1;
};

#define GotoParseNode OneArgParseNode

#define PostIncrementParseNode OneArgParseNode
#define PreIncrementParseNode OneArgParseNode
#define PostDecrementParseNode OneArgParseNode
#define PreDecrementParseNode OneArgParseNode

#define MulParseNode TwoArgParseNode
#define DivParseNode TwoArgParseNode

#define AddParseNode TwoArgParseNode
#define SubParseNode TwoArgParseNode

#define AssignParseNode TwoArgParseNode
#define AddAssignParseNode TwoArgParseNode
#define SubAssignParseNode TwoArgParseNode
#define MulAssignParseNode TwoArgParseNode
#define DivAssignParseNode TwoArgParseNode

struct ConstParseNode
{
	struct Constant value;
};

struct IdentifierParseNode
{
	struct Symbol* identifier;
	char name[IDENTIFIER_NAME_MAX_LEN];
};

// This is never created in the bison file
struct TemporaryVariableParseNode
{
	struct Variable* variable;
};

struct ReturnedVariableParseNode
{
	struct Variable* variable;
};

struct ReturnParseNode
{
	struct ParseNode* returnValue;
};

struct IfParseNode
{
	struct ParseNode* bodyCompoundStatement;
	struct ParseNode* conditionalExpression;
};

struct WhileParseNode
{
	struct ParseNode* bodyCompoundStatement;
	struct ParseNode* conditionalExpression;
};

struct ForParseNode
{
	struct ParseNode* initStatement;
	struct ParseNode* conditionalExpression;
	struct ParseNode* countingStatement;
	struct ParseNode* bodyCompoundStatement;
};


#define COMPOUND_STATEMENT_SIZE 0x100

struct CompoundStatementParseNode
{
	struct ParseNode* statements[COMPOUND_STATEMENT_SIZE];
};

enum EQUALITY_TYPE
{
	ET_E,
	ET_NE,
	ET_G,
	ET_GE,
	ET_L,
	ET_LE
};

struct EqualityParseNode
{
	enum EQUALITY_TYPE eqType;
	struct ParseNode* arg0;
	struct ParseNode* arg1;
};

struct CallParseNode
{
	struct IdentifierParseNode* function;
	struct ParseNode* parametersStart[FUNCTION_PARAMETERS_SIZE];
	struct ParseNode** parametersEnd;
};

/////////////////////////////////////////////////////////////////////////////
// Parse Node Macros/Functions

struct Variable* HasVariable(struct ParseNode* pn);

#define PN_ALLOC(DEST, PN_STRUCT)\
	DEST = (struct ParseNode*)malloc(sizeof(struct ParseNode) + sizeof(PN_STRUCT))

#define PLAIN_PN_ALLOC(DEST, PN_TYPE)\
	DEST = malloc(sizeof(struct ParseNode));\
	PN_SET_TYPE(DEST, PN_TYPE)

#define PN_SET_TYPE(PN, PNT)\
	((struct ParseNode*)(PN))->type = PNT

#define PSUB_PARSENODE(PN, PN_STRUCT)\
	((PN_STRUCT*)(((Int8*)(PN)) + sizeof(struct ParseNode)))