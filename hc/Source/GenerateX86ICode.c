#include "GenerateICode.h"
#include "GenerateX86ICode.h"
#include "Function.h"
#include "ParseNode.h"
#include <stdio.h>
#include <stdlib.h>

// <{IT_.*},
static const char* instructionTypeStrings[] =
{
	"IT_ASSIGN_VAR_TO_VAR",
	"IT_ASSIGN_CONSTANT_TO_VAR",

	"IT_ADD_VAR_TO_VAR",
	"IT_ADD_CONSTANT_TO_VAR",

	"IT_SUB_VAR_FROM_VAR",
	"IT_SUB_CONSTANT_FROM_VAR",

	"IT_MUL_VAR_BY_VAR",
	"IT_MUL_VAR_BY_CONSTANT",

	"IT_DIV_VAR_BY_VAR",
	"IT_DIV_VAR_BY_CONSTANT",

	"IT_RETURN_VOID",
	"IT_RETURN_CONSTANT",
	"IT_RETURN_VAR",

	"IT_CMP_VAR_AND_VAR",
	"IT_CMP_VAR_AND_CONSTANT",
	"IT_CMP_CONSTANT_AND_CONSTANT",
	"IT_SET_CONDITION",
	"IT_JMP",
	"IT_JMP_CONDITION",

	"IT_CALL"
};

void BackPatchCALL(struct BackPatch* bp)
{
	struct Function* f = (struct Function*)bp->extra;
	UInt startFuncToCallOff = (UInt)bp->dest.pointer + 4 - (UInt)f->machineCodeStart;
	UInt callOff = startFuncToCallOff + f->codeStart;
	UInt calledFuncOff = *((UInt*)bp->src.pointer);
	
	Int offset = (Int)calledFuncOff - (Int)callOff;
	*((UInt32*)bp->dest.pointer) = offset;
}

void BackPatchJMP(struct BackPatch* bp)
{
	*((UInt*)bp->dest.pointer) -= bp->extra;
	GenericBackPatcher(bp);
}


// icode -> x86icode
void GenerateX86ICode(struct FunctionTable* ft, struct SymbolTable* gst)
{
	struct Function** fs;
	struct Function* f;
	for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
	{
		struct Instruction* i = (struct Instruction*)f->intermediateCodeStart;
		UInt32 c = 0;
		void* icodeToIMachineCodePs[FUNCTION_INTERMEDIATE_CODE_DATA_SIZE/sizeof(struct Instruction)];
		void** icodeToIMachineCodePsP = icodeToIMachineCodePs;

#if 0
		for (v = (struct Variable*)f->localVariablesStart; v < f->localVariablesEnd; ++v)
		{
			f->localVariablesAlloc += 4;
			v->stackOffset = -((Int)f->localVariablesAlloc);
		}
#endif

		AddPushReg(X86I_R_EBP);
		AddMovRegToReg(X86I_R_EBP, X86I_R_ESP);
		AddSubConstFromReg(X86I_R_ESP, &zero32BitConstant);
		
		// Those instructions are 5 bytes together
		AddGenericBackPatch(f, &f->localVariablesAlloc, sizeof(f->localVariablesAlloc), c, 4, 4);

		while (i < f->intermediateCodeEnd)
		{
			*icodeToIMachineCodePsP++ = f->intermediateMachineCodeEnd;

			printf("%s\n", instructionTypeStrings[i->type]);

			switch (i->type)
			{
			case IT_JMP:
				{
					// We put the addr of the start and end points of the jmp into extra data
					((struct JmpInfo*)f->extraDataEnd)->start = f->intermediateMachineCodeEnd;
					((struct JmpInfo*)f->extraDataEnd)->end = PSUB_INSTRUCTION(i, struct Jmp)->dest;

					ADD_X86IBASICOP(X86I_OT_JMP);
					
					AddGenericBackPatch(f, &(((struct JmpInfo*)f->extraDataEnd)->offset), sizeof(UInt), c, 1, 1);

#if 0
					f->backPatchesEnd->src.pointer = &(((struct JmpInfo*)f->extraDataEnd)->offset);
					f->backPatchesEnd->src.size = sizeof(UInt);
					f->backPatchesEnd->preDest.byteOffset = 0;
					f->backPatchesEnd->preDest.opCode = c;
					f->backPatchesEnd->patcher = BackPatchJMP;
					((struct JmpInfo*)f->extraDataEnd)->bp - f->backPatchesEnd;
					++f->backPatchesEnd;
#endif


					f->extraDataEnd += sizeof(struct JmpInfo);
					ADD_TO_I(struct Jmp);
					break;
				}
			case IT_JMP_CONDITION:
				{
					// We put the addr of the start and end points of the jmp into extra data
					((struct JmpInfo*)f->extraDataEnd)->start = f->intermediateMachineCodeEnd;
					((struct JmpInfo*)f->extraDataEnd)->end = PSUB_INSTRUCTION(i, struct JmpCondition)->dest;

					{
						struct JmpIfCondition* op = ADD_X86IOP(struct JmpIfCondition, X86I_OT_JMP_IF_COND);
						op->condition = PSUB_INSTRUCTION(i, struct JmpCondition)->condition;
					}
					
					AddGenericBackPatch(f, &(((struct JmpInfo*)f->extraDataEnd)->offset), sizeof(UInt), c, 1, 1);

					f->extraDataEnd += sizeof(struct JmpInfo);

					ADD_TO_I(struct JmpCondition);
					break;
				}
			case IT_CMP_VAR_AND_CONSTANT:
				{
					struct CmpDerefRegisterAndConstant* op = ADD_X86IOP(struct CmpDerefRegisterAndConstant, X86I_OT_CMP_DEREFREG_AND_CONST);
					op->constant = PSUB_INSTRUCTION(i, struct CmpVarAndConstant)->arg1;
					op->derefReg.reg = X86I_R_EBP;
					op->derefReg.disp = PSUB_INSTRUCTION(i, struct CmpVarAndConstant)->arg0->stackOffset;
					op->derefReg.scale = 1;

					ADD_TO_I(struct CmpVarAndConstant);
					break;
				}
			case IT_CMP_CONSTANT_AND_CONSTANT:
				{
					struct Constant* arg0 = &PSUB_INSTRUCTION(i, struct CmpConstantAndConstant)->arg0;
					struct Constant* arg1 = &PSUB_INSTRUCTION(i, struct CmpConstantAndConstant)->arg1;

					AddMovConstToReg(X86I_R_ECX, arg0);

					{
						struct CmpRegisterAndConstant* op = ADD_X86IOP(struct CmpRegisterAndConstant, X86I_OT_CMP_REG_AND_CONST);
						op->constant = *arg1;
						op->reg = X86I_R_ECX;
					}

					ADD_TO_I(struct CmpConstantAndConstant);
					break;
				}
			case IT_SET_CONDITION:
				{
					enum CONDITION_CODE cond = PSUB_INSTRUCTION(i, struct SetCondition)->condition;
					struct Variable* dest = PSUB_INSTRUCTION(i, struct SetCondition)->dest;

					{
						struct SetConditionX86I* op = ADD_X86IOP(struct SetConditionX86I, X86I_OT_SET_CONDITION);
						op->condition = cond;
						op->dest.disp = dest->stackOffset;
						op->dest.reg = X86I_R_EBP;
						op->dest.scale = 1;
					}
					
					ADD_TO_I(struct SetCondition);
					break;
				}
			case IT_ASSIGN_VAR_TO_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AssignVarToVarIns)->dest;
					struct Variable* src = PSUB_INSTRUCTION(i, struct AssignVarToVarIns)->src;

					if (src->stackOffset == MAX_INT)
					{
						AddMovRegToDerefEBPWDisp(dest->stackOffset, X86I_R_EAX);
					}
					else
					{
						// 1. MOV [32] REG, [32] var1
						// 2. MOV [32] var0, [32] REG
						AddMovDerefEBPWDispToReg(X86I_R_ECX, src->stackOffset);
						AddMovRegToDerefEBPWDisp(dest->stackOffset, X86I_R_ECX);
					}

					ADD_TO_I(struct AssignVarToVarIns);
					break;
				}
			case IT_ASSIGN_CONSTANT_TO_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AssignConstantToVarIns)->dest;
					struct Constant* src  = &PSUB_INSTRUCTION(i, struct AssignConstantToVarIns)->src;

					// Generate
					// 1. MOV [32] var, CONSTANT
					AddMovConstToDerefEBPWDisp(dest->stackOffset, src);

					ADD_TO_I(struct AssignConstantToVarIns);
					break;
				}
			case IT_ADD_VAR_TO_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->dest;
					struct Variable* src  = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->src;

					// Generate
					// 1. MOV [32] REG, [32] var1
					// 2. ADD [32] var0, [32] REG
					 
					if (src->stackOffset == MAX_INT)
					{
						AddAddRegToDerefEBPWDisp(dest->stackOffset, X86I_R_EAX);
					}
					else
					{
						// 1. MOV [32] REG, [32] var1
						// 2. MOV [32] var0, [32] REG
						AddMovDerefEBPWDispToReg(X86I_R_ECX, src->stackOffset);
						AddAddRegToDerefEBPWDisp(dest->stackOffset, X86I_R_ECX);
					}

					ADD_TO_I(struct AddVarToVarIns);
					break;
				}
			case IT_ADD_CONSTANT_TO_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AddConstantToVarIns)->dest;
					struct Constant* src  = &PSUB_INSTRUCTION(i, struct AddConstantToVarIns)->src;

					// Generate
					// 1. ADD var0, immm

					AddAddConstToDerefEBPWDisp(dest->stackOffset, src);

					ADD_TO_I(struct AddConstantToVarIns);
					break;
				}
			case IT_SUB_VAR_FROM_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->dest;
					struct Variable* src  = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->src;

					// Generate
					// 1. MOV [32] REG, [32] var1
					// 2. ADD [32] var0, [32] REG

					if (src->stackOffset == MAX_INT)
					{
						AddSubRegFromDerefEBPWDisp(dest->stackOffset, X86I_R_EAX);
					}
					else
					{
						// 1. MOV [32] REG, [32] var1
						// 2. MOV [32] var0, [32] REG
						AddMovDerefEBPWDispToReg(X86I_R_ECX, src->stackOffset);
						AddSubRegFromDerefEBPWDisp(dest->stackOffset, X86I_R_ECX);
					}


					ADD_TO_I(struct AddVarToVarIns);
					break;
				}
			case IT_SUB_CONSTANT_FROM_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct SubConstantFromVarIns)->dest;
					struct Constant* src  = &PSUB_INSTRUCTION(i, struct SubConstantFromVarIns)->src;

					// Generate
					// 1. SUB var0, immm

					AddSubConstFromDerefEBPWDisp(dest->stackOffset, src);
					ADD_TO_I(struct SubConstantFromVarIns);
					break;
				}
			case IT_MUL_VAR_BY_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->dest;
					struct Variable* src  = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->src;

					// IMUL reg32,r/m32              ; o32 0F AF /r         [386]
					// Generate
					// mov    ECX, var0
					// imul   ECX, var1
					// mov    var0, ECX

					AddMovDerefEBPWDispToReg(X86I_R_ECX, dest->stackOffset);
					
					{
						struct IMulRegisterByDerefRegister* op = ADD_X86IOP(struct IMulRegisterByDerefRegister, X86I_OT_IMUL_REG_BY_DEREFREG);
						op->dest = X86I_R_ECX;
						op->src.reg = X86I_R_EBP;
						op->src.disp = src->stackOffset;
					}

					ADD_TO_I(struct AddVarToVarIns);
					break;
				}
			case IT_MUL_VAR_BY_CONSTANT:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct MulVarByConstantIns)->dest;
					struct Constant* src  = &PSUB_INSTRUCTION(i, struct MulVarByConstantIns)->src;

					// Generate
					// IMUL ECX, var, imm
					// MOV var, ECX

					struct IMulDerefRegByConstantToReg* op = ADD_X86IOP(struct IMulDerefRegByConstantToReg, X86I_OT_IMUL_DEREFREG_BY_CONST_TO_REG);
					op->dest = X86I_R_ECX;
					op->factor0.reg = X86I_R_EBP;
					op->factor0.disp = dest->stackOffset;
					op->factor1 = *src;

					AddMovRegToDerefEBPWDisp(dest->stackOffset, X86I_R_ECX);

					ADD_TO_I(struct MulVarByConstantIns);
					break;
				}
			case IT_DIV_VAR_BY_VAR:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->dest;
					struct Variable* src  = PSUB_INSTRUCTION(i, struct AddVarToVarIns)->src;

					// Generate
					// MOV ECX, EAX
					// MOV EAX, var0
					// DIV var1
					// MOV var0, EAX
					// MOV EAX, ECX

					// Save EAX
					AddMovRegToReg(X86I_R_ECX, X86I_R_EAX);
					
					AddMovConstToReg(X86I_R_EDX, &zero32BitConstant);
					AddMovDerefEBPWDispToReg(X86I_R_EAX, dest->stackOffset);

					{
						struct IDivDerefRegToEAXAndEDX * op = ADD_X86IOP(struct IDivDerefRegToEAXAndEDX, X86I_OT_IDIV_DEREFREG_TO_EAX_AND_EDX);
						op->divisor.reg = X86I_R_EBP;
						op->divisor.disp = dest->stackOffset;
					}

					AddMovRegToDerefEBPWDisp(dest->stackOffset, X86I_R_EAX);

					// Restore EAX
					AddMovRegToReg(X86I_R_EAX, X86I_R_ECX);


					ADD_TO_I(struct AddVarToVarIns);
					break;
				}
			case IT_DIV_VAR_BY_CONSTANT:
				{
					struct Variable* dest = PSUB_INSTRUCTION(i, struct DivVarByConstantIns)->dest;
					struct Constant* src  = &PSUB_INSTRUCTION(i, struct DivVarByConstantIns)->src;

					// Generate
					// MOV ECX, EAX
					// MOV EAX, var
					// MOV EBX, imm
					// DIV EBX
					// MOV var, EAX
					// MOV EAX, ECX
					
					// Save EAX
					AddMovRegToReg(X86I_R_ECX, X86I_R_EAX);

					AddMovConstToReg(X86I_R_EDX, &zero32BitConstant);
					//AddMovDerefEBPWDispToReg(X86I_R_DX, dest->stackOffset + variableTypeSizes[dest->type]/2);
					AddMovDerefEBPWDispToReg(X86I_R_EAX, dest->stackOffset);
					AddMovConstToReg(X86I_R_EBX, src);
					{
						struct IDivRegToEAXAndEDX * op = ADD_X86IOP(struct IDivRegToEAXAndEDX, X86I_OT_IDIV_REG_TO_EAX_AND_EDX);
						op->divisor = X86I_R_EBX;
					}
					AddMovRegToDerefEBPWDisp(dest->stackOffset, X86I_R_EAX);
					AddMovRegToReg(X86I_R_EAX, X86I_R_ECX);

					ADD_TO_I(struct DivVarByConstantIns);
					break;
				}
			case IT_CALL:
				{
					struct ParseNode** ps;
					struct CallIns* ci = PSUB_INSTRUCTION(i, struct CallIns);
					struct Constant bytesToPop;
					bytesToPop.type = CT_UINT32;
					bytesToPop.u32 = 0;
					
					// Push arguments (in reverse order)
					for (ps = ci->parametersEnd - 1; ps >= ci->parametersStart; --ps)
					{
						struct Variable* v;
						if ((v = HasVariable(*ps)))
						{
							AddPushDerefEBPWDisp(v->stackOffset);

							bytesToPop.u32 += variableTypeSizes[v->type.specifier];
							// TODO WRITE GetSizeOfVariable
						}
						else
						{
							AddPushConst(PSUB_PARSENODE(*ps, struct ConstParseNode)->value);

							bytesToPop.u32 += constantTypeSizes[PSUB_PARSENODE(*ps, struct ConstParseNode)->value.type];
						}

						
					}

					ADD_X86ICALL();

					AddAddConstToReg(X86I_R_ESP, &bytesToPop);

					// Back patch the offset from the calling address to the function start
					f->backPatchesEnd->preDest.opCode = c - 1;
					f->backPatchesEnd->preDest.byteOffset = 4;
					f->backPatchesEnd->src.pointer = &(PSUB_SYMBOL(ci->function, struct FunctionSymbol)->function->codeStart);
					f->backPatchesEnd->patcher = BackPatchCALL;
					f->backPatchesEnd->extra = (UInt)f;
					++f->backPatchesEnd;


					ADD_TO_I(struct CallIns);
					break;
				}
			case IT_RETURN_CONSTANT:
				{
					const struct Constant* src = &(PSUB_INSTRUCTION(i, struct ReturnConstant)->returnValue);
					AddMovConstToReg(X86I_R_EAX, src);
					
					ADD_TO_I(struct ReturnConstant);
					goto ReturnVoidCase;
				}
			case IT_RETURN_VAR:
				{
					const struct Variable* src = (PSUB_INSTRUCTION(i, struct ReturnVar)->returnValue);
					AddMovDerefEBPWDispToReg(X86I_R_EAX, src->stackOffset);
					
					ADD_TO_I(struct ReturnVar);
					goto ReturnVoidCase;;
				}
			case IT_RETURN_VOID:
				{
ReturnVoidCase:
					ADD_X86ILEAVE();
					ADD_X86IRETN();

					//AddGenericBackPatch(f, &f->sizeOfParameters, sizeof(f->sizeOfParameters), c, 2, 2);

					break;
				}
			
			default:
				{
					COMPILER_ERRORF("%s not implemented", instructionTypeStrings[i->type]);
					continue;
				}
			}
		}


		// JMP offsets

		i = (struct Instruction*)f->intermediateCodeStart;
		c = 0;

		while (i < f->intermediateCodeEnd)
		{
			struct JmpInfo* p;
			for (p = (struct JmpInfo*)f->extraDataStart; (void*)p < (void*)f->extraDataEnd; ++p)
			{
				if (p->end == (void*)i)
					p->end = (void*)icodeToIMachineCodePs[c];
			}

			ADD_BYTES_TO_P(i, struct Instruction*, instructionSizes[i->type] + sizeof(struct Instruction));
			++c;
		}
	}
}
