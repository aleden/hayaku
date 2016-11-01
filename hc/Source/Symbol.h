#pragma once
#include "Common.h"
#include "Variable.h"

enum SYMBOL_TYPE
{
	ST_VARIABLE,
	ST_FUNCTION,
	ST_LABEL
};

struct Symbol
{
	enum SYMBOL_TYPE type;
	char name[IDENTIFIER_NAME_MAX_LEN];
};

static const UInt symbolSizes[] = 
{
	sizeof(void*), // ST_VARIABLE
	sizeof(void*), // ST_FUNCTION
	sizeof(UInt), // ST_LABEL
};

// Sub classes of Symbol

struct VariableSymbol
{
	// For intermediate code, NULL if variable does not exist
	struct Variable* variable;
};

struct FunctionSymbol
{
	struct Function* function;
};

struct TypedefSymbol
{
	struct VariableType type;
};

#if 0
struct ClassSymbol
{
	//Variable
};
#endif

struct LabelSymbol
{
	UInt instructionCount;
};

#define SYMBOL_TABLE_DATA_SIZE sizeof(struct Symbol) * 0x40

struct SymbolTable
{
	UInt8 symbolsStart[SYMBOL_TABLE_DATA_SIZE];
	UInt8* symbolsEnd;
};

#define PSUB_SYMBOL(S, SUB_STRUCT)\
	((SUB_STRUCT*)(((Int8*)(S)) + sizeof(struct Symbol)))

void InitializeSymbolTable(struct SymbolTable* st);

extern struct SymbolTable* gst;
extern struct FunctionTable* ft;

BOOL DoesIdentifierSymbolExist(struct SymbolTable* st, char* ascii);
struct Symbol* FindIdentifierSymbol(struct SymbolTable* gst, struct SymbolTable* lst, char* ascii);

struct Function* FindFunctionByName(char* ascii);
struct Symbol* FindFunctionSymbolByName(char* ascii);

struct Symbol* AddVariableSymbol(struct Function* f, char* ascii, struct Variable* v);
struct Symbol* AddFunctionSymbol(struct SymbolTable* st, char* ascii, struct Function* f);