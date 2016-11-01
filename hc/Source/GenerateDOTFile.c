#include "GenerateDOTFile.h"
#include "ParseNode.h"
#include "Symbol.h"
#include "ICode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

UInt c;

// {\t}{[A-Z_]*}{\,}
// \1\"\2\"\3
extern const char* parseNodeTypeStrings[];

static void PutConstParseNodeIntoBuff(char* buff, struct ConstParseNode* cpn, UInt* c)
{
	switch (cpn->value.type)
	{
	case CT_INT:
	case CT_INT8:
	case CT_INT16:
	case CT_INT32:
		sprintf(buff, "%d[%u]", cpn->value.i, (*c)++);
		break;
	case CT_INT64:
		sprintf(buff, "%ld[%u]", cpn->value.i64, (*c)++);
		break;

	case CT_UINT:
	case CT_UINT8:
	case CT_UINT16:
	case CT_UINT32:
		sprintf(buff, "%u[%u]", cpn->value.u, (*c)++);
		break;
	case CT_UINT64:
		sprintf(buff, "%lu[%u]", cpn->value.u64, (*c)++);
		break;

	case CT_FLOAT:
	case CT_FLOAT32:
	case CT_FLOAT64:
		sprintf(buff, "%f[%u]", cpn->value.f64, (*c)++);
		break;
	}
}

static void GenerateDOTR(FILE* dotFile, struct ParseNode* pn, char* parentName)
{
	UInt finalBuffSize = 0;
	Int8 finalBuff[0x100];
	char* me;

	// Determine me
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
	case PNT_GOTO:
	case PNT_PRE_INCREMENT:
	case PNT_POST_INCREMENT:
	case PNT_PRE_DECREMENT:
	case PNT_POST_DECREMENT:
	case PNT_TEMP_VAR:
	case PNT_RET:
	case PNT_RET_VOID:
	case PNT_CALL:
		me = malloc(strlen(parseNodeTypeStrings[pn->type] + 4) + 1);
		sprintf(me, "%s[%u]", parseNodeTypeStrings[pn->type] + 4, c++);
		break;

	case PNT_IDENTIFIER:
		me = malloc(strlen(PSUB_PARSENODE(pn, struct IdentifierParseNode)->identifier->name) + 1);
		sprintf(me, "%s[%u]", PSUB_PARSENODE(pn, struct IdentifierParseNode)->identifier->name, c++);
		break;

	case PNT_CONST:
		me = malloc(0x100);
		PutConstParseNodeIntoBuff(me, PSUB_PARSENODE(pn, struct ConstParseNode), &c);
		break;
	}

	finalBuffSize = sprintf(finalBuff, "\"%s\" -- \"%s\";\n", parentName, me);
	fwrite(finalBuff, sizeof(char), finalBuffSize, dotFile);

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
		{
			struct ParseNode* arg0 = PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0;
			struct ParseNode* arg1 = PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1;
			GenerateDOTR(dotFile, arg0, me);
			GenerateDOTR(dotFile, arg1, me);
		}
		break;

	case PNT_GOTO:
	case PNT_PRE_INCREMENT:
	case PNT_POST_INCREMENT:
	case PNT_PRE_DECREMENT:
	case PNT_POST_DECREMENT:
	case PNT_IDENTIFIER:
	case PNT_TEMP_VAR:
	case PNT_CONST:
		break;
	case PNT_RET:
		GenerateDOTR(dotFile, PSUB_PARSENODE(pn, struct ReturnParseNode)->returnValue, me);
		break;
	}
}

void GenerateDOTFile(struct FunctionTable* ft, struct SymbolTable* gst, const char* filePath)
{
	static const char str[] = "graph graphname {\n";
	FILE* dotFile;
	struct ParseNode* pn;
	struct Function** fs;
	struct Function* f;

	c = 1;

	dotFile = fopen(filePath, "w");
	fwrite(str, sizeof(char), sizeof(str) - 1, dotFile);

	for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
	{
		struct ParseNode** pns;
		for (pns = (struct ParseNode**)f->body->statements, pn = *pns; *pns; ++pns, pn = *pns)
		{
			Int8 startName[0x100];

			sprintf(startName, "%s[%u]", parseNodeTypeStrings[pn->type] + 4, c);
			printf("startName = %s\n", startName);

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
				{
					struct ParseNode* arg0 = PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0;
					struct ParseNode* arg1 = PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1;
					GenerateDOTR(dotFile, arg0, startName);
					GenerateDOTR(dotFile, arg1, startName);
				}
				break;

			case PNT_GOTO:
			case PNT_PRE_INCREMENT:
			case PNT_POST_INCREMENT:
			case PNT_PRE_DECREMENT:
			case PNT_POST_DECREMENT:
			case PNT_TEMP_VAR:
			case PNT_IDENTIFIER:
			case PNT_CONST:
				break;

			case PNT_RET:
				GenerateDOTR(dotFile, PSUB_PARSENODE(pn, struct ReturnParseNode)->returnValue, startName);
				break;
			}
		}

	}

	fwrite("}\n", sizeof(char), 2, dotFile);

	fclose(dotFile);
}
