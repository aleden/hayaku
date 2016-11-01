#include "Link.h"
#include "ICode.h"
#include <string.h>
#include <stdlib.h>
#include "WritePEFile.h"

void Link(FILE* exeFile, struct FunctionTable* ft, const char* entryPoint)
{
	struct Function* f;
	struct Function** fs;
	UInt codeSize;

	// Set entry point function to be first
	for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
	{
		if (strcmp(f->name, entryPoint) == 0)
		{
			struct Function* temp = *ft->functions;
			*ft->functions = f;
			*fs = temp;
			break;
		}
	}

	// Calculate total code size and offsets
	codeSize = 0;
	for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
	{
		f->codeStart = codeSize;
		codeSize += f->machineCodeEnd - f->machineCodeStart;
	}

	// Write back patches
	for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
	{
		struct BackPatch* bpp;
		for (bpp = (struct BackPatch*)f->backPatchesStart; bpp < f->backPatchesEnd; ++bpp)
		{
			(*bpp->patcher)(bpp);
		}
	}

	{
		UInt offset = 0;
		struct PEFileSection textSect;
		struct PEFileCreationParams p;

		textSect.attr = PFSAF_EXECUTE | PFSAF_READ;
		textSect.size = elevateToPEPageSizeMultiple(codeSize);
		textSect.data = malloc(textSect.size);

		for (fs = ft->functions, f = *fs; *fs; ++fs, f = *fs)
		{
			codeSize = (UInt)(f->machineCodeEnd - f->machineCodeStart);
			memcpy(((UInt8*)textSect.data) + offset, f->machineCodeStart, codeSize);
			offset += codeSize;
		}

		p.machineType = MT_IA32;
		p.numSections = 1;
		p.sections = (struct PEFileSection**)malloc(sizeof(struct PEFileSection*));
		*p.sections = &textSect;

		printf("\nWriting WIN32 PE File...\n\n");
		WritePEFile(exeFile, &p);
	}
}