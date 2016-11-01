#pragma once
#include "Types.h"
#include "CompileConfig.h"
#include <stdio.h>

#define IDENTIFIER_NAME_MAX_LEN 0x100

//#ifdef _MSC_VER
//    #define inline static __inline
//#endif

#ifndef BOOL
	#define BOOL Int
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#ifndef TRUE
	#define TRUE 1
#endif

#ifdef _MSC_VER
    #define DEBUG_BREAK __asm int 3
#else
    #define DEBUG_BREAK asm("int #3")
#endif

#define ADD_BYTES_TO_P(P, PTYPE, NUM_BYTES)\
	P = (PTYPE)((Int8*)(P) + (NUM_BYTES))

#define COPY_C_ARRAY(DEST_MEM, DEST_NUM, SRC_MEM, SRC_NUM, ARRAY_ELEMENT_SIZE)\
		memcpy(DEST_MEM, SRC_MEM, SRC_NUM * ARRAY_ELEMENT_SIZE);\
		DEST_NUM = SRC_NUM

#define PSUBCLASS(POINTER, BASE, SUB) ((SUB*)(sizeof(BASE) + ((char*)(POINTER))))
#define PSUBBYTEOFF(POINTER, OFF, SUB) ((SUB*)(OFF + ((char*)(POINTER))))

enum CONSTANT_TYPE
{
	CT_INT, // Word size
	CT_INT8,
	CT_INT16,
	CT_INT32,
	CT_INT64,

	CT_UINT, // Word size
	CT_UINT8,
	CT_UINT16,
	CT_UINT32,
	CT_UINT64,

	CT_FLOAT, // Word size
	CT_FLOAT32,
	CT_FLOAT64
};

#define CONSTANT_VALUE\
	union\
	{\
		Int i;\
		Int8 i8;\
		Int16 i16;\
		Int32 i32;\
		Int64 i64;\
		\
		UInt u;\
		UInt8 u8;\
		UInt16 u16;\
		UInt32 u32;\
		UInt64 u64;\
		\
		Float f;\
		Float32 f32;\
		Float64 f64;\
	}

struct Constant
{
	CONSTANT_VALUE;
	enum CONSTANT_TYPE type;
};

static const struct Constant zero32BitConstant = {0, CT_INT32};

static const UInt constantTypeSizes[] =
{
	4, // Word size
	1,
	2,
	4,
	8,

	4, // Word size
	1,
	2,
	4,
	8,

	4, // Word size
	4,
	8
};

#define CONSTANT_FIELD(NAME)\
	enum CONSTANT_TYPE NAME##Type;\
	union Constant NAME

enum ERROR_LEVEL
{
	EL_LOW,
	EL_MEDIUM,
	EL_HIGH,
	EL_CRITICAL
};

#if defined (DEBUG) && defined (WIN32)
	#define COMPILER_ERROR(ERROR_MESSAGE)\
		{\
			printf("ERROR: %s\n", ERROR_MESSAGE);\
			system("pause");\
			exit(0);\
		}
#else
	#define COMPILER_ERROR(ERROR_MESSAGE)\
		{\
			printf("ERROR: %s\n", ERROR_MESSAGE);\
			exit(0);\
		}
#endif

#ifdef WIN32
	#ifdef DEBUG
		#define COMPILER_ERRORF(ERROR_MESSAGE, ...)\
			{\
				printf("ERROR: " ERROR_MESSAGE "\n", __VA_ARGS__);\
				system("pause");\
				exit(0);\
			}
	#else
		#define COMPILER_ERRORF(ERROR_MESSAGE, ...)\
			{\
				printf("ERROR: " ERROR_MESSAGE "\n", __VA_ARGS__);\
				exit(0);\
			}
	#endif
#elif defined (LINUX)
	#define COMPILER_ERRORF(ERROR_MESSAGE, ...)\
		{\
			printf("ERROR: " ERROR_MESSAGE "\n", #__VA_ARGS__);\
			exit(0);\
		}
#endif

#define ASSERT(BOOL)\
	if (!(BOOL)) COMPILER_ERRORF("ASSERT() failure at %s (%d)", __FILE__, __LINE__)

#define SWAPUINT32(a, b) ((((UInt32)(a)) ^= ((UInt32)(b))), (((UInt32)(b)) ^= ((UInt32)(a))), (((UInt32)(a)) ^= ((UInt32)(b))))