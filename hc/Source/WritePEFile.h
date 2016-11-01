#pragma once
#include "Common.h"
#include <stdio.h>
#include "Link.h"
#include "ICode.h"

#define PE_PAGE_SIZE 0x1000

enum MACHINE_TYPE
{
	MT_IA32,
	MT_IA64
};

enum PE_FILE_SECTION_ATTR_FLAG
{
	PFSAF_EXECUTE = 0x20000000,
	PFSAF_READ = 0x40000000,
	PFSAF_WRITE = 0x80000000
};

struct PEFileCreationParams
{
	enum MACHINE_TYPE machineType;

	UInt numSections;
	struct PEFileSection** sections;
};

struct PEFileSection
{
	UInt attr;
	void* data;
	UInt size;
};

void WritePEFile(FILE* file, struct PEFileCreationParams* params);

UInt elevateToPEPageSizeMultiple(UInt n);