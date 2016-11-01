#include "GenerateX86Code.h"
#include "GenerateX86ICode.h"
#include "ICode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Sources for x86 machine code specifications:
// http://courses.ece.illinois.edu/ece390/books/labmanual/inst-ref.html
// http://www.intel.com/design/intarch/manuals/243191.htm

#define out (f->machineCodeEnd)

#define ADD_TO_O(X86IOP_STRUCT)\
	o = ((struct X86IOperation*)(((Int8*)o) + sizeof(struct X86IOperation) + sizeof(X86IOP_STRUCT)))

#define RECORD_OPERATION(SIZE)\
	*opOffsets++ = (f->machineCodeEnd - f->machineCodeStart) - (SIZE);\
	++c

#define IS_BETWEEN(VAL, START, END) ((VAL) >= (START) && (VAL) <= (END))
#define IS_INT8(VAL) (IS_BETWEEN((VAL), -128, 127))
#define IS_INT16(VAL) (IS_BETWEEN((VAL), -32768, 32767))

// mod - [0,3] (2 bits)
// reg - [0,7] (3 bits)
// rm  - [0,7] (3 bits)
#define MAKE_MOD_RM_BYTE(mod, reg, rm) (((UInt8)(rm)) | (((UInt8)(reg)) << 3) | (((UInt8)(mod)) << 6))

#define REG32LABELS \
	case X86I_R_EAX:\
	case X86I_R_ECX:\
	case X86I_R_EDX:\
	case X86I_R_EBX:\
	case X86I_R_ESP:\
	case X86I_R_EBP:\
	case X86I_R_ESI:\
	case X86I_R_EDI

#define REG16LABELS \
	case X86I_R_AX:\
	case X86I_R_CX:\
	case X86I_R_DX:\
	case X86I_R_BX:\
	case X86I_R_SP:\
	case X86I_R_BP:\
	case X86I_R_SI:\
	case X86I_R_DI

#define REG8LABELS \
	case X86I_R_AL:\
	case X86I_R_CL:\
	case X86I_R_DL:\
	case X86I_R_BL:\
	case X86I_R_AH:\
	case X86I_R_CH:\
	case X86I_R_DH:\
	case X86I_R_BH

#define GEN_CONST_TO_DEREFREG_OP(OPCODE, OPCODE8, MODRM_REG)\
	{\
		const struct DerefRegister* const dest = &PSUB_X86IOP(o, struct ConstantToDerefRegister)->dest;\
		const struct Constant* const src = &PSUB_X86IOP(o, struct ConstantToDerefRegister)->src;\
		UInt insSize = 0;\
		\
		switch (dest->reg)\
		{\
		REG32LABELS:\
			*out++ = (OPCODE);\
			++insSize;\
			break;\
		REG16LABELS:\
			*out++ = 0x66;\
			*out++ = (OPCODE);\
			insSize += 2;\
			break;\
		REG8LABELS:\
			*out++ = OPCODE8;\
			++insSize;\
			break;\
		}\
		\
		if (IS_INT8(dest->disp))\
		{\
			*out++ = MAKE_MOD_RM_BYTE(1, MODRM_REG, dest->reg);\
			*((Int8*)out) = dest->disp;\
			++out;\
			*((Int32*)out) = src->i32;\
			out += 4;\
			insSize += 6;\
		}\
		else\
		{\
			*out++ = MAKE_MOD_RM_BYTE(2, MODRM_REG, dest->reg);\
			*((Int32*)out) = dest->disp;\
			out += 4;\
			*((Int32*)out) = src->i32;\
			out += 4;\
			insSize += 9;\
		}\
		\
		RECORD_OPERATION(insSize);\
		ADD_TO_O(struct ConstantToDerefRegister);\
	}\
	break;

// MOV reg32,r/m32 ; o32 8B /r [386]
// MOV reg16,r/m16 ; o16 8B /r [8086]
// MOV reg8,r/m8   ; 8A /r     [8086]
#define GEN_DEREFREG_TO_REG_OP(OPCODE, OPCODE8)\
	{\
		enum X86I_REGISTER dest = PSUB_X86IOP(o, struct DerefRegisterToRegister)->dest;\
		const struct DerefRegister* const src = &PSUB_X86IOP(o, struct DerefRegisterToRegister)->src;\
		UInt insSize = 0;\
		\
		switch (dest)\
		{\
		REG32LABELS:\
			*out++ = (OPCODE);\
			++insSize;\
			break;\
			\
		REG16LABELS:\
			*out++ = 0x66;\
			*out++ = (OPCODE);\
			insSize += 2;\
			dest -= X86I_R_AX;\
			break;\
			\
		REG8LABELS:\
			*out++ = (OPCODE8);\
			++insSize;\
			dest -= X86I_R_AL;\
			break;\
		}\
		\
		if (src->disp == 0)\
		{\
			*out++ = MAKE_MOD_RM_BYTE(0, dest, src->reg);\
			++insSize;\
		}\
		else if (IS_INT8(src->disp))\
		{\
			*out++ = MAKE_MOD_RM_BYTE(1, dest, src->reg);\
			*((Int8*)out) = src->disp;\
			++out;\
			insSize += 2;\
		}\
		else\
		{\
			*out++ = MAKE_MOD_RM_BYTE(2, dest, src->reg);\
			*((Int32*)out) = src->disp;\
			out += 4;\
			insSize += 5;\
		}\
		\
		RECORD_OPERATION(insSize);\
		ADD_TO_O(struct DerefRegisterToRegister);\
	}\
	break;\

// mod = 3
// rm = reg
#define GEN_REG_TO_REGE_OP(OPCODE, OPCODE8)\
	{\
		enum X86I_REGISTER dest = PSUB_X86IOP(o, struct RegisterToRegister)->dest;\
		enum X86I_REGISTER src = PSUB_X86IOP(o, struct RegisterToRegister)->src;\
		UInt insSize = 0;\
		\
		switch (src)\
		{\
			REG32LABELS:\
				*out++ = (OPCODE);\
				++insSize;\
				break;\
				\
			REG16LABELS:\
				*out++ = 0x66;\
				*out++ = (OPCODE);\
				insSize += 2;\
				src -= X86I_R_AX;\
				dest -= X86I_R_AX;\
				break;\
				\
			REG8LABELS:\
				*out++ = (OPCODE8);\
				++insSize;\
				src -= X86I_R_AL;\
				dest -= X86I_R_AX;\
				break;\
		}\
		\
		*out++ = MAKE_MOD_RM_BYTE(3, src, dest);\
		++insSize;\
		\
		RECORD_OPERATION(insSize);\
		ADD_TO_O(struct RegisterToRegister);\
	}\
	break;

// ADD r/m8,reg8   ; 00 /r     [8086]
// ADD r/m16,reg16 ; o16 01 /r [8086]
// ADD r/m32,reg32 ; o32 01 /r [386]
#define GEN_REG_TO_DEREFREG_OP(OPCODE, OPCODE8)\
	{\
		const struct DerefRegister* const dest = &PSUB_X86IOP(o, struct RegisterToDerefRegister)->dest;\
		enum X86I_REGISTER src = PSUB_X86IOP(o, struct RegisterToDerefRegister)->src;\
		UInt insSize = 0;\
		\
		switch (src)\
		{\
			REG32LABELS:\
				*out++ = (OPCODE);\
				++insSize;\
				break;\
				\
			REG16LABELS:\
				*out++ = 0x66;\
				*out++ = (OPCODE);\
				insSize += 2;\
				src -= X86I_R_AX;\
				break;\
				\
			REG8LABELS:\
				*out++ = (OPCODE8);\
				++insSize;\
				src -= X86I_R_AL;\
				break;\
		}\
		\
		if (dest->disp == 0)\
		{\
			*out++ = MAKE_MOD_RM_BYTE(0, src, dest->reg);\
			++insSize;\
		}\
		else if (IS_INT8(dest->disp))\
		{\
			*out++ = MAKE_MOD_RM_BYTE(1, src, dest->reg);\
			*((Int8*)out) = dest->disp;\
			++out;\
			insSize += 2;\
		}\
		else\
		{\
			*out++ = MAKE_MOD_RM_BYTE(2, src, dest->reg);\
			*((Int32*)out) = dest->disp;\
			out += 4;\
			insSize += 5;\
		}\
		\
		RECORD_OPERATION(insSize);\
		ADD_TO_O(struct RegisterToDerefRegister);\
	}\
	break;

#define GEN_CONST_TO_REG_OPADDEDTOOPCODE(OPCODE, OPCODE8)\
	{\
		const enum X86I_REGISTER reg = PSUB_X86IOP(o, struct ConstantToRegister)->dest;\
		const struct Constant* const src = &PSUB_X86IOP(o, struct ConstantToRegister)->src;\
		\
		switch (reg)\
		{\
		REG32LABELS:\
			*out++ = (OPCODE) + reg;\
			*((Int32*)out) = src->i32;\
			out += 4;\
			\
			RECORD_OPERATION(sizeof(UInt8) + sizeof(Int32));\
			break;\
			\
		REG16LABELS:\
			*out++ = 0x66;\
			*out++ = (OPCODE) + (reg - X86I_R_AX);\
			*((Int16*)out) = src->i16;\
			out += 2;\
			RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int16));\
			break;\
			\
		REG8LABELS:\
			*out++ = (OPCODE8) + (reg - X86I_R_AL);\
			*((Int8*)out) = src->i8;\
			++out;\
			RECORD_OPERATION(sizeof(UInt8) + sizeof(Int8));\
			break;\
		}\
	}\
	ADD_TO_O(struct ConstantToRegister);\
	break;


// <{X86I_OT_.*},
static const char* x86OperationTypeStrings[] =
{
	"X86I_OT_PUSH_REG",
	"X86I_OT_PUSH_DEEREFREG",
	"X86I_OT_PUSH_CONST",

	"X86I_OT_MOV_REG_TO_REG",
	"X86I_OT_ADD_REG_TO_REG",
	"X86I_OT_SUB_REG_FROM_REG",

	"X86I_OT_MOV_CONST_TO_DEREFREG",
	"X86I_OT_ADD_CONST_TO_DEREFREG",
	"X86I_OT_SUB_CONST_FROM_DEREFREG",

	"X86I_OT_MOV_CONST_TO_REG",
	"X86I_OT_ADD_CONST_TO_REG",
	"X86I_OT_SUB_CONST_FROM_REG",

	"X86I_OT_MOV_DEREFREG_TO_REG",
	"X86I_OT_ADD_DEREFREG_TO_REG",
	"X86I_OT_SUB_DEREFREG_FROM_REG",

	"X86I_OT_MOV_REG_TO_DEREFREG",
	"X86I_OT_ADD_REG_TO_DEREFREG",
	"X86I_OT_SUB_REG_FROM_DEREFREG",
	
	"X86I_OT_IMUL_DEREFREG_BY_CONST_TO_REG",
	"X86I_OT_IMUL_REG_BY_DEREFREG",
	"X86I_OT_IMUL_REG_BY_CONST",

	"X86I_OT_IDIV_DEREFREG_TO_EAX_AND_EDX",
	"X86I_OT_IDIV_REG_TO_EAX_AND_EDX",

	"X86I_OT_INC_REG",
	"X86I_OT_CMP_REG_AND_CONST",
	"X86I_OT_CMP_DEREFREG_AND_CONST",
	"X86I_OT_SET_CONDITION",
	"X86I_OT_JMP_IF_COND",
	"X86I_OT_JMP",

	"X86I_OT_CALL",
	"X86I_OT_LEAVE",
	"X86I_OT_RETN"
};

/*
0000 O Overflow
0001 NO No overflow
0010 B, NAE Below, Not above or equal
0011 NB, AE Not below, Above or equal
0100 E, Z Equal, Zero
0101 NE, NZ Not equal, Not zero
0110 BE, NA Below or equal, Not above
0111 NBE, A Not below or equal, Above
1000 S Sign
1001 NS Not sign
1010 P, PE Parity, Parity Even
1011 NP, PO Not parity, Parity Odd
1100 L, NGE Less than, Not greater than or equal to
1101 NL, GE Not less than, Greater than or equal to
1110 LE, NG Less than or equal to, Not greater than
1111 NLE, G Not less than or equal to, Greater than
*/
static const Int8 x86ConditionCodesTable[] = 
{
	4, // CC_E
	5, // CC_NE
	15, // CC_G
	13, // CC_GE
	12, // CC_L
	14, // CC_LE
	4, // CC_Z
	5 // CC_NZ
};



// x86icode -> x86code
void GenerateX86Code(struct FunctionTable* ft, struct SymbolTable* gst)
{
	struct Function** fs;
	struct Function* f;
	for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
	{
		struct BackPatch* bpp = (struct BackPatch*)f->backPatchesStart;
		UInt opOffsetsSize;
		UInt* opOffsets;
		struct X86IOperation* o = (struct X86IOperation*)f->intermediateMachineCodeStart;
		UInt c = 0;

		opOffsetsSize = sizeof(UInt) * (((UInt8*)f->intermediateMachineCodeEnd) - ((UInt8*)f->intermediateMachineCodeStart));
		opOffsets = (UInt*)malloc(opOffsetsSize);
		memset(opOffsets, 0xFF, opOffsetsSize);

		// 0+rw PUSH r16 Push r16
		// 50+rd PUSH r32 Push r32

		while ((void*)o < (void*)f->intermediateMachineCodeEnd)
		{

			printf("%s\n", x86OperationTypeStrings[o->type]);

			// For JMP offsets
			{
				struct JmpInfo* p;
				for (p = (struct JmpInfo*)f->extraDataStart; (void*)p < (void*)f->extraDataEnd; ++p)
				{
					if (p->start == (void*)o)
					{
						p->start = (void*)f->machineCodeEnd;
						
						if (IS_BETWEEN((void*)p->start, (void*)f->machineCodeStart, (void*)f->machineCodeEnd) &&
							IS_BETWEEN((void*)p->end, (void*)f->machineCodeStart, (void*)f->machineCodeEnd))
						{
							p->offset = (UInt)((UInt8*)p->end - (UInt8*)p->start) - 2;
						}
					}
					else if (p->end == (void*)o)
					{
						p->end = (void*)f->machineCodeEnd;

						if (IS_BETWEEN((void*)p->start, (void*)f->machineCodeStart, (void*)f->machineCodeEnd) &&
							IS_BETWEEN((void*)p->end, (void*)f->machineCodeStart, (void*)f->machineCodeEnd))
						{
							p->offset = (UInt)((UInt8*)p->end - (UInt8*)p->start) - 2;
						}
					}
				}
			}


			switch (o->type)
			{
			case X86I_OT_JMP:
				{
					// JMP imm ; E9 rw/rd [8086]
					// JMP SHORT imm ; EB rb [8086]
					*out++ = 0xEB;
					*out++ = 0xFF; // To be back patched

					RECORD_OPERATION(sizeof(UInt8)*2);
				}
				++o;
				break;

			case X86I_OT_JMP_IF_COND:
				{
					// 0F 80+cc rw/rd
					// Jcc imm ; 70+cc rb [8086]
					*out++ = 0x70 + x86ConditionCodesTable[PSUB_X86IOP(o, struct JmpIfCondition)->condition];
					*out++ = 0xFF; // To be back patched

					RECORD_OPERATION(sizeof(UInt8) * 2);
				}
				ADD_TO_O(struct JmpIfCondition);
				break;

			case X86I_OT_PUSH_REG:
				{
					*out++ = 0x50 + PSUB_X86IOP(o, struct PushRegister)->reg;
					RECORD_OPERATION(sizeof(UInt8));
				}
				ADD_TO_O(struct PushRegister);
				break;

			case X86I_OT_PUSH_DEEREFREG:
				{
					// PUSH r/m16 ; o16 FF /6 [8086]
					// PUSH r/m32 ; o32 FF /6 [386]

					const struct DerefRegister* const dest = &PSUB_X86IOP(o, struct PushDerefRegister)->derefReg;
					UInt insSize;
				
					switch (dest->reg)
					{
						REG32LABELS:
							*out++ = 0xFF;
							insSize = 0;
							break;
						
						REG16LABELS:
							*out++ = 0x66;
							*out++ = 0xFF;
							insSize = 2;
							break;
						
						REG8LABELS:
							ASSERT(0);
							break;
					}
				
					if (dest->disp == 0)
					{
						*out++ = MAKE_MOD_RM_BYTE(0, 6, dest->reg);
						++insSize;
					}
					else if (IS_INT8(dest->disp))
					{
						*out++ = MAKE_MOD_RM_BYTE(1, 6, dest->reg);
						*((Int8*)out) = dest->disp;
						++out;
						insSize += 2;
					}
					else
					{
						*out++ = MAKE_MOD_RM_BYTE(2, 6, dest->reg);
						*((Int32*)out) = dest->disp;
						out += 4;
						insSize += 5;
					}
				
					RECORD_OPERATION(insSize);
				}
				
				ADD_TO_O(struct PushDerefRegister);
				break;
				
			case X86I_OT_SET_CONDITION:
				{
					// SETcc r/m8 ; 0F 90+cc /2 [386]
					*out++ = 0x0F;
					*out++ = 0x90 + x86ConditionCodesTable[PSUB_X86IOP(o, struct SetConditionX86I)->condition];
					*out++ = MAKE_MOD_RM_BYTE(2, 2, PSUB_X86IOP(o, struct SetConditionX86I)->dest.reg);
					*((Int32*)out) = PSUB_X86IOP(o, struct SetConditionX86I)->dest.disp;
					out += 4;
					RECORD_OPERATION(sizeof(UInt8)*3 + sizeof(UInt32));
				}
				ADD_TO_O(struct SetConditionX86I);
				break;

			case X86I_OT_PUSH_CONST:
				{
					struct Constant* constant = &(PSUB_X86IOP(o, struct PushConstant)->constant);

					switch (constantTypeSizes[constant->type])
					{
					case 1:
						*out++ = 0x6A;
						*out++ = constant->u8;
						RECORD_OPERATION(sizeof(UInt8) * 2);
						break;
					case 2:
						*out++ = 0x66;
						*out++ = 0x68;
						*((UInt16*)out) = constant->u16;
						out += 2;
						RECORD_OPERATION(sizeof(UInt8) * 2 + sizeof(UInt16));
						break;
					case 4:
						*out++ = 0x68;
						*((UInt32*)out) = constant->u32;
						out += 4;
						RECORD_OPERATION(sizeof(UInt8) + sizeof(UInt32));
						break;
					}
				}
				ADD_TO_O(struct PushConstant);
				break;

			case X86I_OT_MOV_CONST_TO_REG:
				GEN_CONST_TO_REG_OPADDEDTOOPCODE(0xB8, 0xB0);
				break;

			case X86I_OT_MOV_REG_TO_REG:
				GEN_REG_TO_REGE_OP(0x89, 0x88);
				break;

			case X86I_OT_MOV_CONST_TO_DEREFREG:
				GEN_CONST_TO_DEREFREG_OP(0xC7, 0xC6, 0);
				break;

			case X86I_OT_MOV_DEREFREG_TO_REG:
				GEN_DEREFREG_TO_REG_OP(0x8B, 0x8A);
				break;

			case X86I_OT_MOV_REG_TO_DEREFREG:
				GEN_REG_TO_DEREFREG_OP(0x89, 0x8A);
				break;

			case X86I_OT_ADD_CONST_TO_DEREFREG:
				GEN_CONST_TO_DEREFREG_OP(0x81, 0x80, 0);
				break;

			case X86I_OT_ADD_REG_TO_DEREFREG:
				GEN_REG_TO_DEREFREG_OP(0x01, 0x00);
				break;

			case X86I_OT_SUB_CONST_FROM_DEREFREG:
				GEN_CONST_TO_DEREFREG_OP(0x81, 0x80, 5);
				break;

			case X86I_OT_SUB_REG_FROM_DEREFREG:
				GEN_REG_TO_DEREFREG_OP(0x29, 0);
				break;

			case X86I_OT_IMUL_REG_BY_DEREFREG:
				{
					enum X86I_REGISTER dest = PSUB_X86IOP(o, struct IMulRegisterByDerefRegister)->dest;
					const struct DerefRegister* src = &PSUB_X86IOP(o, struct IMulRegisterByDerefRegister)->src;

					switch (dest)
					{
					REG32LABELS:
						break;
					REG16LABELS:
						dest -= X86I_R_AX;
						break;
					default:
						COMPILER_ERROR("Invalid register");
					}

					*out++ = 0x0F;
					*out++ = 0xAF;

					if (IS_INT8(src->disp))
					{
						*out++ = MAKE_MOD_RM_BYTE(1, dest, src->reg);
						*((Int8*)out) = src->disp;
						++out;
						RECORD_OPERATION(sizeof(UInt8)*4);
					}
					else
					{
						*out++ = MAKE_MOD_RM_BYTE(2, dest, src->reg);
						*((Int32*)out) = src->disp;
						out += 4;
						RECORD_OPERATION(sizeof(UInt8)*3 + sizeof(Int32));
					}
				}
				ADD_TO_O(struct IMulRegisterByDerefRegister);
				break;

			case X86I_OT_IMUL_DEREFREG_BY_CONST_TO_REG:
				{
					enum X86I_REGISTER dest = PSUB_X86IOP(o, struct IMulDerefRegByConstantToReg)->dest;
					const struct DerefRegister* factor0 = &PSUB_X86IOP(o, struct IMulDerefRegByConstantToReg)->factor0;
					const struct Constant* factor1 = &PSUB_X86IOP(o, struct IMulDerefRegByConstantToReg)->factor1;

					switch (dest)
					{
					REG32LABELS:
						break;
					REG16LABELS:
						dest -= X86I_R_AX;
						break;
					default:
						COMPILER_ERROR("Invalid register");
					}

					*out++ = 0x69;

					if (IS_INT8(factor0->disp))
					{
						*out++ = MAKE_MOD_RM_BYTE(1, dest, factor0->reg);
						*((Int8*)out) = factor0->disp;
						++out;
						*((Int32*)out) = factor1->i32;
						out += 4;
						RECORD_OPERATION(sizeof(UInt8)*3 + sizeof(Int32));
					}
					else
					{
						*out++ = MAKE_MOD_RM_BYTE(2, dest, factor0->reg);
						*((Int32*)out) = factor0->disp;
						out += 4;
						*((Int32*)out) = factor1->i32;
						out += 4;
						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int32)*2);
					}
				}
				ADD_TO_O(struct IMulDerefRegByConstantToReg);
				break;

			case X86I_OT_IDIV_DEREFREG_TO_EAX_AND_EDX:
				{
					const struct DerefRegister* divisor = &PSUB_X86IOP(o, struct IDivDerefRegToEAXAndEDX)->divisor;
					UInt insSize = 0;

					switch (divisor->reg)
					{
					REG32LABELS:
						*out++ = 0xF7;
						++insSize;
						break;

					REG16LABELS:
						*out++ = 0x66;
						*out++ = 0xF7;
						insSize += 2;
						divisor -= X86I_R_AX;
						break;

					REG8LABELS:
						*out++ = 0xF6;
						++insSize;
						divisor -= X86I_R_AL;
						break;
					}

					if (divisor->disp == 0)
					{
						*out++ = MAKE_MOD_RM_BYTE(0, 7, divisor->reg);
						++insSize;
					}
					else if (IS_INT8(divisor->disp))
					{
						*out++ = MAKE_MOD_RM_BYTE(1, 7, divisor->reg);
						*((Int8*)out) = divisor->disp;
						++out;
						insSize += 2;
					}
					else
					{
						*out++ = MAKE_MOD_RM_BYTE(2, 7, divisor->reg);
						*((Int32*)out) = divisor->disp;
						out += 4;
						insSize += 5;
					}

					RECORD_OPERATION(insSize);
				}
				ADD_TO_O(struct IDivDerefRegToEAXAndEDX);
				break;

			case X86I_OT_IDIV_REG_TO_EAX_AND_EDX:
				{
					enum X86I_REGISTER divisor = PSUB_X86IOP(o, struct IDivRegToEAXAndEDX)->divisor;
					UInt insSize = 0;

					switch (divisor)
					{
					REG32LABELS:
						*out++ = 0xF7;
						++insSize;
						break;

					REG16LABELS:
						*out++ = 0x66;
						*out++ = 0xF7;
						insSize += 2;
						divisor -= X86I_R_AX;
						break;

					REG8LABELS:
						*out++ = 0xF6;
						++insSize;
						divisor -= X86I_R_AL;
						break;
					}

					*out++ = MAKE_MOD_RM_BYTE(3, 7, divisor);
					++insSize;
					RECORD_OPERATION(insSize);
				}
				ADD_TO_O(struct IDivRegToEAXAndEDX);
				break;

			case X86I_OT_CMP_DEREFREG_AND_CONST:
				GEN_CONST_TO_DEREFREG_OP(0x81, 0x80, 7);
				break;

			case X86I_OT_CMP_REG_AND_CONST:
				{
					const enum X86I_REGISTER reg = ((struct CmpRegisterAndConstant*)(o + 1))->reg;
					const struct Constant* const constant = &PSUB_X86IOP(o, struct CmpRegisterAndConstant)->constant;

					switch (reg)
					{
						case X86I_R_AL:
							*out++ = 0x3C;
							*((Int8*)out) = constant->i8;
							++out;

							RECORD_OPERATION(sizeof(UInt8) + sizeof(Int8));
							break;
						case X86I_R_AX:
							*out++ = 0x66;
							*out++ = 0x3D;
							*((Int16*)out) = constant->i16;
							out += 2;

							RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int16));
							break;
						case X86I_R_EAX:
							*out++ = 0x3D;
							*((Int32*)out) = constant->i32;
							out += 4;

							RECORD_OPERATION(sizeof(UInt8) + sizeof(Int32));
							break;
						case X86I_R_ECX:
						case X86I_R_EDX:
						case X86I_R_EBX:
						case X86I_R_ESP:
						case X86I_R_EBP:
						case X86I_R_ESI:
						case X86I_R_EDI:
							*out++ = 0x81;
							*out++ = MAKE_MOD_RM_BYTE(3, 7, reg);
							*((Int32*)out) = constant->i32;
							out += 4;

							RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int32));
							break;

						case X86I_R_CX:
						case X86I_R_DX:
						case X86I_R_BX:
						case X86I_R_SP:
						case X86I_R_BP:
						case X86I_R_SI:
						case X86I_R_DI:
							*out++ = 0x66;
							*out++ = 0x81;
							*out++ = MAKE_MOD_RM_BYTE(3, 7, reg - X86I_R_AX);
							*((Int16*)out) = constant->i16;
							out += 2;

							RECORD_OPERATION(sizeof(UInt8)*3 + sizeof(Int16));
							break;

						case X86I_R_CL:
						case X86I_R_DL:
						case X86I_R_BL:
						case X86I_R_AH:
						case X86I_R_CH:
						case X86I_R_DH:
						case X86I_R_BH:
							*out++ = 0x80;
							*out++ = MAKE_MOD_RM_BYTE(3, 7, reg - X86I_R_AL);
							*((Int8*)out) = constant->i8;
							++out;

							RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int8));
							break;
					}
				}
				ADD_TO_O(struct CmpRegisterAndConstant);
				break;

			case X86I_OT_SUB_CONST_FROM_REG:
				{
					const enum X86I_REGISTER dest = PSUB_X86IOP(o, struct AddConstantToRegister)->dest;
					const struct Constant* const src = &PSUB_X86IOP(o, struct AddConstantToRegister)->src;

					switch (dest)
					{
					case X86I_R_AL:
						*out++ = 0x2C;
						*((Int8*)out) = src->i8;
						++out;

						RECORD_OPERATION(sizeof(UInt8)*2);
						break;
					case X86I_R_AX:
						*out++ = 0x66;
						*out++ = 0x2D;
						*((Int16*)out) = src->i16;
						out += 2;

						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int16));
						break;
					case X86I_R_EAX:
						*out++ = 0x2D;
						*((Int32*)out) = src->i32;
						out += 4;

						RECORD_OPERATION(sizeof(UInt8) + sizeof(Int32));
						break;
					case X86I_R_ECX:
					case X86I_R_EDX:
					case X86I_R_EBX:
					case X86I_R_ESP:
					case X86I_R_EBP:
					case X86I_R_ESI:
					case X86I_R_EDI:
						*out++ = 0x81;
						*out++ = MAKE_MOD_RM_BYTE(3, 5, dest);
						*((Int32*)out) = src->i32;
						out += 4;

						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int32));
						break;

					case X86I_R_CX:
					case X86I_R_DX:
					case X86I_R_BX:
					case X86I_R_SP:
					case X86I_R_BP:
					case X86I_R_SI:
					case X86I_R_DI:
						*out++ = 0x66;
						*out++ = 0x81;
						*out++ = MAKE_MOD_RM_BYTE(3, 5, dest - X86I_R_AX);
						*((Int16*)out) = src->i16;
						out += 2;

						RECORD_OPERATION(sizeof(UInt8)*3 + sizeof(Int16));
						break;

					case X86I_R_CL:
					case X86I_R_DL:
					case X86I_R_BL:
					case X86I_R_AH:
					case X86I_R_CH:
					case X86I_R_DH:
					case X86I_R_BH:
						*out++ = 0x80;
						*out++ = MAKE_MOD_RM_BYTE(3, 5, dest - X86I_R_AL);
						*((Int8*)out) = src->i8;
						++out;

						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int8));
						break;
					}
				}
				ADD_TO_O(struct SubConstantFromRegister);
				break;

			case X86I_OT_ADD_CONST_TO_REG:
				{
					const enum X86I_REGISTER dest = PSUB_X86IOP(o, struct AddConstantToRegister)->dest;
					const struct Constant* const src = &PSUB_X86IOP(o, struct AddConstantToRegister)->src;

					switch (dest)
					{
						//     ADD r/m32,imm32               ; o32 81 /0 id         [386]
        
    // ADD AL,imm8                   ; 04 ib                [8086]
    // ADD AX,imm16                  ; o16 05 iw            [8086]
    // ADD EAX,imm32                 ; o32 05 id            [386]

					case X86I_R_AL:
						*out++ = 0x04;
						*((Int8*)out) = src->i8;
						++out;

						RECORD_OPERATION(sizeof(UInt8)*2);
						break;
					case X86I_R_AX:
						*out++ = 0x66;
						*out++ = 0x05;
						*((Int16*)out) = src->i16;
						out += 2;

						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int16));
						break;
					case X86I_R_EAX:
						*out++ = 0x05;
						*((Int32*)out) = src->i32;
						out += 4;

						RECORD_OPERATION(sizeof(UInt8) + sizeof(Int32));
						break;
					case X86I_R_ECX:
					case X86I_R_EDX:
					case X86I_R_EBX:
					case X86I_R_ESP:
					case X86I_R_EBP:
					case X86I_R_ESI:
					case X86I_R_EDI:
						*out++ = 0x81;
						*out++ = MAKE_MOD_RM_BYTE(3, 0, dest);
						*((Int32*)out) = src->i32;
						out += 4;

						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int32));
						break;

					case X86I_R_CX:
					case X86I_R_DX:
					case X86I_R_BX:
					case X86I_R_SP:
					case X86I_R_BP:
					case X86I_R_SI:
					case X86I_R_DI:
						*out++ = 0x66;
						*out++ = 0x81;
						*out++ = MAKE_MOD_RM_BYTE(3, 0, dest - X86I_R_AX);
						*((Int16*)out) = src->i16;
						out += 2;

						RECORD_OPERATION(sizeof(UInt8)*3 + sizeof(Int16));
						break;

					case X86I_R_CL:
					case X86I_R_DL:
					case X86I_R_BL:
					case X86I_R_AH:
					case X86I_R_CH:
					case X86I_R_DH:
					case X86I_R_BH:
						*out++ = 0x80;
						*out++ = MAKE_MOD_RM_BYTE(3, 0, dest - X86I_R_AL);
						*((Int8*)out) = src->i8;
						++out;

						RECORD_OPERATION(sizeof(UInt8)*2 + sizeof(Int8));
						break;
					}
				}
				ADD_TO_O(struct AddConstantToRegister);
				break;

			case X86I_OT_INC_REG:
				{
					const enum X86I_REGISTER reg = PSUB_X86IOP(o, struct IncRegister)->reg;

					switch (reg)
					{
					REG32LABELS:
						*out++ = 0x40 + reg;
						RECORD_OPERATION(sizeof(UInt8));
						break;

					REG16LABELS:
						*out++ = 0x66;
						*out++ = 0x40 + (reg - X86I_R_AX);
						RECORD_OPERATION(sizeof(UInt8)*2);
						break;

					REG8LABELS:
						*out++ = 0xFE;
						*out++ = MAKE_MOD_RM_BYTE(3, 0, reg - X86I_R_AL);
						RECORD_OPERATION(sizeof(UInt8)*2);
						break;
					}
				}
				ADD_TO_O(struct IncRegister);
				break;

			case X86I_OT_CALL:
				{
					*out++ = 0xE8;
					// rel32
					*((Int32*)out) = (-0x6A + - 0x17);
					out += 4;
					RECORD_OPERATION(sizeof(UInt8) + sizeof(UInt32));
				}
				++o;
				break;

			case X86I_OT_LEAVE:
				{
					*out++ = 0xC9;
					RECORD_OPERATION(sizeof(UInt8));
				}
				++o;
				break;

			case X86I_OT_RETN:
				{
#if 0
					*out++ = 0xC2;
					*((UInt16*)out) = 0xDEAD; // To be back patched
					out += 2;
					RECORD_OPERATION(sizeof(UInt8) + sizeof(UInt16));
#else
					*out++ = 0xC3;
					RECORD_OPERATION(sizeof(UInt8));
#endif
				}
				++o;
				break;

			default:
				{
					COMPILER_ERRORF("%s not implemented", x86OperationTypeStrings[o->type]);
					continue;
				}
			}
			{
				struct BackPatch* bpp2 = bpp;
				while (bpp2 < f->backPatchesEnd)
				{
					if (bpp2->preDest.opCode == c)
					{
						bpp2->dest.pointer = ((UInt8*)out - bpp2->preDest.byteOffset);
						bpp = bpp2 + 1;
						break;
					}
					else if (bpp2->preDest.opCode > c)
					{
						break;
					}

					++bpp2;
				}
			}
		}
	}
}
