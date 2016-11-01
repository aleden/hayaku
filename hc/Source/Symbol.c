#include "Symbol.h"
#include "GenerateICode.h"
#include <string.h>

BOOL DoesIdentifierSymbolExist(struct SymbolTable* st, char* ascii)
{
	struct Symbol* s;
	for (s = (struct Symbol*)st->symbolsStart;
		 s != (struct Symbol*)st->symbolsEnd;
		 ADD_BYTES_TO_P(s, struct Symbol*, sizeof(struct Symbol) + symbolSizes[s->type]))
	{
		if (strcmp(s->name, ascii) == 0)
			return TRUE;
	}

	return FALSE;
}

#define SEARCH_ST(ASCII, ST)\
	struct Symbol* s;\
	for (s = (struct Symbol*)(ST)->symbolsStart;\
		 s < (struct Symbol*)(ST)->symbolsEnd;\
		 ADD_BYTES_TO_P(s, struct Symbol*, sizeof(struct Symbol) + symbolSizes[s->type]))\
	{\
		if (strcmp(s->name, ascii) == 0)\
			return s;\
	}

struct Symbol* FindIdentifierSymbol(struct SymbolTable* gst, struct SymbolTable* lst, char* ascii)
{
	struct Symbol* s;
	for (s = (struct Symbol*)gst->symbolsStart;
		 s < (struct Symbol*)gst->symbolsEnd;
		 ADD_BYTES_TO_P(s, struct Symbol*, sizeof(struct Symbol) + symbolSizes[s->type]))
	{
		if (strcmp(s->name, ascii) == 0)
			return s;
	}

	for (s = (struct Symbol*)lst->symbolsStart;
		 s < (struct Symbol*)lst->symbolsEnd;
		 ADD_BYTES_TO_P(s, struct Symbol*, sizeof(struct Symbol) + symbolSizes[s->type]))
	{
		if (strcmp(s->name, ascii) == 0)
			return s;
	}
	return NULL;
}

struct Function* FindFunctionByName(char* ascii)
{
	struct Function** fs;
	for (fs = ft->functions; *fs; ++fs)
	{
		if (strcmp((*fs)->name, ascii) == 0)
			return *fs;
	}
}

struct Symbol* FindFunctionSymbolByName(char* ascii)
{
	struct Symbol* s;
	for (s = (struct Symbol*)gst->symbolsStart; (void*)s < (void*)gst->symbolsEnd; s += symbolSizes[s->type])
	{
		if (s->type == ST_FUNCTION && strcmp(s->name, ascii) == 0)
			return s;
	}

	return NULL;
}


static struct Symbol* AddIdentifier(struct SymbolTable* st, char* ascii, enum SYMBOL_TYPE type)
{
	struct Symbol* s = (struct Symbol*)st->symbolsEnd;
	s->type = type;
	strcpy(s->name, ascii);
	ADD_BYTES_TO_P(st->symbolsEnd, UInt8*, sizeof(struct Symbol));

	return s;
}

struct Symbol* AddVariableSymbol(struct Function* f, char* ascii, struct Variable* v)
{
	struct Symbol* s = AddIdentifier(&f->symbolTable, ascii, ST_VARIABLE);
	PSUB_SYMBOL(s, struct VariableSymbol)->variable = v;
	ADD_BYTES_TO_P(f->symbolTable.symbolsEnd, UInt8*, sizeof(struct VariableSymbol));

	return s;
}

struct Symbol* AddFunctionSymbol(struct SymbolTable* st, char* ascii, struct Function* f)
{
	struct Symbol* s = AddIdentifier(st, ascii, ST_FUNCTION);
	PSUB_SYMBOL(s, struct FunctionSymbol)->function = f;
	ADD_BYTES_TO_P(st->symbolsEnd, UInt8*, sizeof(struct FunctionSymbol));

	return s;
}

void InitializeSymbolTable(struct SymbolTable* st)
{
	st->symbolsEnd = st->symbolsStart;
}