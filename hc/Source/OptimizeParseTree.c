#include "OptimizeParseTree.h"
#include "ParseNode.h"
#include <stdio.h>

static void OptimizeParseTreeR(struct ParseNode* pn)
{
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
		OptimizeParseTreeR(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg0);
		OptimizeParseTreeR(PSUB_PARSENODE(pn, struct TwoArgParseNode)->arg1);
		break;

	case PNT_GOTO:
	case PNT_PRE_INCREMENT:
	case PNT_POST_INCREMENT:
	case PNT_PRE_DECREMENT:
	case PNT_POST_DECREMENT:
		OptimizeParseTreeR(PSUB_PARSENODE(pn, struct OneArgParseNode)->arg0);
		break;

    case PNT_TEMP_VAR:
	case PNT_IDENTIFIER:
	case PNT_CONST:
		break;
	}

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
	case PNT_IDENTIFIER:
	case PNT_CONST:
	case PNT_TEMP_VAR:
		break;
	}
}

void OptimizeParseTree()
{
#if 0
	struct ParseNode** pns;
	for (pns = 0 + 1; *pns; ++pns)
	{
		OptimizeParseTreeR(*pns);
		printf("EOS\n");
	}
#endif
}