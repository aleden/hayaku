#include "ICode.h"
#include <string.h>
#include <stdlib.h>

void InitializeFunction(struct Function* f)
{
	InitializeSymbolTable(&f->symbolTable);

	memset(f->backPatchesStart, 0, sizeof(UInt8) * FUNCTION_BACK_PATCHES_DATA_SIZE);
	memset(f->parametersStart, 0, sizeof(struct VariableType) * FUNCTION_PARAMETERS_SIZE);
	memset(f->extraDataStart, 0, FUNCTION_EXTRA_DATA_SIZE);

	f->extraDataEnd = f->extraDataStart;
	f->parametersEnd = f->parametersStart;
	f->parameterVariablesAlloc = 0;
	f->parseTreeEnd = (struct ParseNode*)f->parseTreeStart;
	f->localVariablesEnd = (struct Variable*)f->localVariablesStart;
	f->localVariablesAlloc = 0;
	f->intermediateCodeEnd = (struct Instruction*)f->intermediateCodeStart;
	f->intermediateMachineCodeEnd = f->intermediateMachineCodeStart;
	f->machineCodeEnd = f->machineCodeStart;
	f->backPatchesEnd = (struct BackPatch*)f->backPatchesStart;
}

void InitializeFunctionTable(struct FunctionTable* ft)
{
	memset(ft, 0, sizeof(struct FunctionTable));

	// Allocate first function (BUT DO NOT ADD TO SYMBOL TABLE)
	ALLOC_FUNCTION(ft);
}

void GenericBackPatcher(struct BackPatch* patch)
{
	switch (patch->dest.size)
	{
	case 1:
		switch (patch->src.size)
		{
		case 1:
			*((UInt8*)patch->dest.pointer) = (UInt8)(*((UInt8*)(patch->src.pointer)));
			break;
		case 2:
			*((UInt8*)patch->dest.pointer) = (UInt8)(*((UInt16*)patch->src.pointer));
			break;
		case 4:
			*((UInt8*)patch->dest.pointer) = (UInt8)(*((UInt32*)patch->src.pointer));
			break;
		}
		break;

	case 2:
		switch (patch->src.size)
		{
		case 1:
			*((UInt16*)patch->dest.pointer) = (UInt16)(*((UInt8*)patch->src.pointer));
			break;
		case 2:
			*((UInt16*)patch->dest.pointer) = (UInt16)(*((UInt16*)patch->src.pointer));
			break;
		case 4:
			*((UInt16*)patch->dest.pointer) = (UInt16)(*((UInt32*)patch->src.pointer));
			break;
		}
		break;

	case 4:
		switch (patch->src.size)
		{
		case 1:
			*((UInt32*)patch->dest.pointer) = (UInt32)(*((UInt8*)patch->src.pointer));
			break;
		case 2:
			*((UInt32*)patch->dest.pointer) = (UInt32)(*((UInt16*)patch->src.pointer));
			break;
		case 4:
			*((UInt32*)patch->dest.pointer) = (UInt32)(*((UInt32*)patch->src.pointer));
			break;
		}
		break;

	default:
		ASSERT(0);
	}
}

void AddGenericBackPatch(struct Function* f,
                         void* srcPointer,
                         UInt srcSize,
                         UInt pdOpCode,
                         UInt pdByteOffset,
                         UInt destSize)
{
		f->backPatchesEnd->src.pointer = srcPointer;
		f->backPatchesEnd->src.size = srcSize;
		f->backPatchesEnd->preDest.opCode = pdOpCode;
		f->backPatchesEnd->preDest.byteOffset = pdByteOffset;
		f->backPatchesEnd->dest.size = destSize;
		f->backPatchesEnd->patcher = GenericBackPatcher;
		++f->backPatchesEnd;
}