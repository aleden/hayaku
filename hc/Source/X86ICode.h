#pragma once
#include "Common.h"
#include "ICode.h"

#define X86I_CODE_DATA_SIZE 0x10000

enum X86I_REGISTER
{
	// General Purpose 32 Bit Register Names
	X86I_R_EAX, X86I_R_ECX, X86I_R_EDX, X86I_R_EBX, X86I_R_ESP, X86I_R_EBP, X86I_R_ESI, X86I_R_EDI,

	// General Purpose 16 Bit Registers Names
	X86I_R_AX, X86I_R_CX, X86I_R_DX, X86I_R_BX, X86I_R_SP, X86I_R_BP, X86I_R_SI, X86I_R_DI,

	// General Purpose 8 Bit Registers Names
	X86I_R_AL, X86I_R_CL, X86I_R_DL, X86I_R_BL, X86I_R_AH, X86I_R_CH, X86I_R_DH, X86I_R_BH
};

enum X86I_OPERATION_TYPE
{
	X86I_OT_PUSH_REG,
	X86I_OT_PUSH_DEEREFREG,
	X86I_OT_PUSH_CONST,

	X86I_OT_MOV_REG_TO_REG,
	X86I_OT_ADD_REG_TO_REG,
	X86I_OT_SUB_REG_FROM_REG,

	X86I_OT_MOV_CONST_TO_DEREFREG,
	X86I_OT_ADD_CONST_TO_DEREFREG,
	X86I_OT_SUB_CONST_FROM_DEREFREG,

	X86I_OT_MOV_CONST_TO_REG,
	X86I_OT_ADD_CONST_TO_REG,
	X86I_OT_SUB_CONST_FROM_REG,

	X86I_OT_MOV_DEREFREG_TO_REG,
	X86I_OT_ADD_DEREFREG_TO_REG,
	X86I_OT_SUB_DEREFREG_FROM_REG,

	X86I_OT_MOV_REG_TO_DEREFREG,
	X86I_OT_ADD_REG_TO_DEREFREG,
	X86I_OT_SUB_REG_FROM_DEREFREG,
	
	X86I_OT_IMUL_DEREFREG_BY_CONST_TO_REG,
	X86I_OT_IMUL_REG_BY_DEREFREG,
	X86I_OT_IMUL_REG_BY_CONST,

	X86I_OT_IDIV_DEREFREG_TO_EAX_AND_EDX,
	X86I_OT_IDIV_REG_TO_EAX_AND_EDX,

	X86I_OT_INC_REG,
	X86I_OT_CMP_REG_AND_CONST,
	X86I_OT_CMP_DEREFREG_AND_CONST,
	X86I_OT_SET_CONDITION,
	X86I_OT_JMP_IF_COND,
	X86I_OT_JMP,

	X86I_OT_CALL,
	X86I_OT_LEAVE,
	X86I_OT_RETN
};

struct X86IOperation
{
	enum X86I_OPERATION_TYPE type;
};

// Subclasses of X86IOperation

// Generics
struct ConstantToRegister
{
	enum X86I_REGISTER dest;
	struct Constant src;
};

struct DerefRegister
{
	enum X86I_REGISTER reg;
	Int32 disp;
	UInt8 scale;
};

struct RegisterToRegister
{
	enum X86I_REGISTER dest;
	enum X86I_REGISTER src;
};

struct RegisterToDerefRegister
{
	struct DerefRegister dest;
	enum X86I_REGISTER src;
};

struct DerefRegisterToRegister
{
	enum X86I_REGISTER dest;
	struct DerefRegister src;
};

struct ConstantToDerefRegister
{
	struct DerefRegister dest;
	struct Constant src;
};

struct RegisterAndConstant
{
	enum X86I_REGISTER reg;
	struct Constant constant;
};

struct DerefRegisterAndConstant
{
	struct DerefRegister derefReg;
	struct Constant constant;
};

struct ConstantArg
{
	struct Constant constant;
};

struct RegisterArg
{
	enum X86I_REGISTER reg;
};

struct DerefRegArg
{
	struct DerefRegister derefReg;
};

// Actual

#define MovRegisterToRegister RegisterToRegister
#define AddRegisterToRegister RegisterToRegister
#define SubRegisterFromRegister RegisterToRegister

#define MovConstantToDerefRegister ConstantToDerefRegister
#define AddConstantToDerefRegister ConstantToDerefRegister
#define SubConstantFromDerefRegister ConstantToDerefRegister

#define MovConstantToRegister ConstantToRegister
#define AddConstantToRegister ConstantToRegister
#define SubConstantFromRegister ConstantToRegister
#define IMulRegisterByConstant ConstantToRegister

#define MovDerefRegisterToRegister DerefRegisterToRegister
#define AddDerefRegisterToRegister DerefRegisterToRegister
#define SubDerefRegisterFromRegister DerefRegisterToRegister
#define IMulRegisterByDerefRegister DerefRegisterToRegister

#define MovRegisterToDerefRegister RegisterToDerefRegister
#define AddRegisterToDerefRegister RegisterToDerefRegister
#define SubRegisterFromDerefRegister RegisterToDerefRegister

#define CmpRegisterAndConstant RegisterAndConstant
#define CmpDerefRegisterAndConstant DerefRegisterAndConstant

#define IncRegister RegisterArg
#define PushRegister RegisterArg

#define PushConstant ConstantArg
#define PushDerefRegister DerefRegArg

struct SetConditionX86I
{
	struct DerefRegister dest;
	enum CONDITION_CODE condition;
};

struct IMulDerefRegByConstantToReg
{
	enum X86I_REGISTER dest;

	struct DerefRegister factor0;
	struct Constant factor1;
};

struct IDivDerefRegToEAXAndEDX
{
	struct DerefRegister divisor;
};

struct IDivRegToEAXAndEDX
{
	enum X86I_REGISTER divisor;
};

struct JmpIfCondition
{
	enum CONDITION_CODE condition;
};

struct JmpInfo
{
	void* start;
	void* end;
	UInt offset;
	struct BackPatch* bp;
};

struct Call
{
	UInt offset;
};

/////

#define ADD_X86IBASICOP(X86IOP_TYPE)\
	((struct X86IOperation*)f->intermediateMachineCodeEnd)->type = (X86IOP_TYPE);\
	ADD_BYTES_TO_P(f->intermediateMachineCodeEnd, UInt8*, sizeof(struct X86IOperation));\
	++c

#define ADD_X86IOP(X86IOP_STRUCT, X86IOP_TYPE)\
	((X86IOP_STRUCT*)(((struct X86IOperation*)f->intermediateMachineCodeEnd) + 1));\
	((struct X86IOperation*)f->intermediateMachineCodeEnd)->type = X86IOP_TYPE;\
	ADD_BYTES_TO_P(f->intermediateMachineCodeEnd, UInt8*, sizeof(X86IOP_STRUCT) + sizeof(struct X86IOperation));\
	++c

#define ADD_X86ILEAVE()\
	ADD_X86IBASICOP(X86I_OT_LEAVE);

#define ADD_X86IRETN()\
	ADD_X86IBASICOP(X86I_OT_RETN);

#define ADD_X86ICALL()\
	ADD_X86IBASICOP(X86I_OT_CALL);

#define PSUB_X86IOP(O, SUB) ((SUB*)(((Int8*)(O)) + sizeof(struct X86IOperation)))

#define ADD_TO_I(ISTRUCT)\
	i = ((struct Instruction*)(((Int8*)i) + sizeof(struct Instruction) + sizeof(ISTRUCT)))

#define AddSubConstToReg(X86IOP_STRUCT, X86IOP_TYPE, DEST, SRC)\
	{\
		X86IOP_STRUCT* op = ADD_X86IOP(X86IOP_STRUCT, X86IOP_TYPE);\
		op->dest = DEST;\
		op->src = *SRC;\
	}

#define AddSubRegToReg(X86IOP_STRUCT, X86IOP_TYPE, DEST, SRC)\
	{\
		X86IOP_STRUCT* op = ADD_X86IOP(X86IOP_STRUCT, X86IOP_TYPE);\
		op->dest = DEST;\
		op->src = SRC;\
	}

#define AddSubDerefEBPWDispToReg(X86IOP_STRUCT, X86IOP_TYPE, DEST, SRC)\
	{\
		X86IOP_STRUCT* op = ADD_X86IOP(X86IOP_STRUCT, X86IOP_TYPE);\
		op->dest = DEST;\
		op->src.reg = X86I_R_EBP;\
		op->src.disp = SRC;\
		op->src.scale = 1;\
	}

#define AddSubConstToDerefEBPWDisp(X86IOP_STRUCT, X86IOP_TYPE, DEST, SRC)\
	{\
		X86IOP_STRUCT* op = ADD_X86IOP(X86IOP_STRUCT, X86IOP_TYPE);\
		op->src = *(SRC);\
		op->dest.reg = X86I_R_EBP;\
		op->dest.disp = DEST;\
		op->dest.scale = 1;\
	}

#define AddSubRegToDerefEBPWDisp(X86IOP_STRUCT, X86IOP_TYPE, DEST, SRC)\
	{\
		X86IOP_STRUCT* op1 = ADD_X86IOP(X86IOP_STRUCT, X86IOP_TYPE);\
		op1->dest.reg = X86I_R_EBP;\
		op1->dest.disp = DEST;\
		op1->dest.scale = 0;\
		op1->src = SRC;\
	}

//

#define AddMovConstToReg(DEST, SRC)\
	AddSubConstToReg(struct MovConstantToRegister, X86I_OT_MOV_CONST_TO_REG, DEST, (SRC))

#define AddAddConstToReg(DEST, SRC)\
	AddSubConstToReg(struct AddConstantToRegister, X86I_OT_ADD_CONST_TO_REG, DEST, SRC)

#define AddSubConstFromReg(DEST, SRC)\
	AddSubConstToReg(struct SubConstantFromRegister, X86I_OT_SUB_CONST_FROM_REG, DEST, SRC)

//

#define AddMovRegToReg(DEST, SRC)\
	AddSubRegToReg(struct MovRegisterToRegister, X86I_OT_MOV_REG_TO_REG, DEST, SRC)

//

#define AddMovDerefEBPWDispToReg(DEST, SRC)\
	AddSubDerefEBPWDispToReg(struct MovDerefRegisterToRegister, X86I_OT_MOV_DEREFREG_TO_REG, DEST, SRC)

#define AddAddDerefEBPWDispToReg(DEST, SRC)\
	AddSubDerefEBPWDispToReg(struct AddDerefRegisterToRegister, X86I_OT_ADD_DEREFREG_TO_REG, DEST, SRC)

#define AddSubDerefEBPWDispFromReg(DEST, SRC)\
	AddSubDerefEBPWDispToReg(struct SubDerefRegisterFromRegister, X86I_OT_SUB_DEREFREG_FROM_REG, DEST, SRC)

//

#define AddMovRegToDerefEBPWDisp(DEST, SRC)\
	AddSubRegToDerefEBPWDisp(struct MovRegisterToDerefRegister, X86I_OT_MOV_REG_TO_DEREFREG, DEST, SRC)

#define AddAddRegToDerefEBPWDisp(DEST, SRC)\
	AddSubRegToDerefEBPWDisp(struct AddRegisterToDerefRegister, X86I_OT_ADD_REG_TO_DEREFREG, DEST, SRC)

#define AddSubRegFromDerefEBPWDisp(DEST, SRC)\
	AddSubRegToDerefEBPWDisp(struct SubRegisterFromDerefRegister, X86I_OT_SUB_REG_FROM_DEREFREG, DEST, SRC)

//

#define AddMovConstToDerefEBPWDisp(DEST, SRC)\
	AddSubConstToDerefEBPWDisp(struct MovConstantToDerefRegister, X86I_OT_MOV_CONST_TO_DEREFREG, DEST, SRC)

#define AddAddConstToDerefEBPWDisp(DEST, SRC)\
	AddSubConstToDerefEBPWDisp(struct AddConstantToDerefRegister, X86I_OT_ADD_CONST_TO_DEREFREG, DEST, SRC)

#define AddSubConstFromDerefEBPWDisp(DEST, SRC)\
	AddSubConstToDerefEBPWDisp(struct SubConstantFromDerefRegister, X86I_OT_SUB_CONST_FROM_DEREFREG, DEST, SRC)

#define AddPushReg(SRC)\
	{\
		struct PushRegister* o = ADD_X86IOP(struct PushRegister, X86I_OT_PUSH_REG);\
		o->reg = SRC;\
	}

#define AddPushConst(SRC)\
	{\
		struct PushConstant* o = ADD_X86IOP(struct PushConstant, X86I_OT_PUSH_CONST);\
		o->constant = SRC;\
	}

#define AddPushDerefEBPWDisp(SRC)\
	{\
		struct PushDerefRegister* o = ADD_X86IOP(struct PushDerefRegister, X86I_OT_PUSH_DEEREFREG);\
		o->derefReg.reg = X86I_R_EBP;\
		o->derefReg.disp = SRC;\
		o->derefReg.scale = 0;\
	}