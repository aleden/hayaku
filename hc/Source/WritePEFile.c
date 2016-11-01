#include "WritePEFile.h"
#include "PE.h"
#include "Link.h"
#include "ICode.h"
#include <string.h>
#include <malloc.h>
#include <time.h>

#define FILE_SIZE (sizeof(IMAGE_DOS_HEADER) + 4 + sizeof(IMAGE_FILE_HEADER) + \
	             sizeof(IMAGE_OPTIONAL_HEADER32) + sizeof(IMAGE_SECTION_HEADER) + 3)

static void DumpPEFileInfo(FILE* peFile);

static UInt RoundToNextPowerOf2(UInt n)
{
	--n;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	++n;

	return n;
}

UInt elevateToPEPageSizeMultiple(UInt n)
{
	if (n < PE_PAGE_SIZE)
		return PE_PAGE_SIZE;

	return RoundToNextPowerOf2(n);
}

void WritePEFile(FILE* file, struct PEFileCreationParams* params)
{
	struct PEFileSection* s;
	UInt8 blankPage[PE_PAGE_SIZE] = {0};
	UInt i, j;

	// The only two fields that matter are e_magic and e_lfanew
	static const IMAGE_DOS_HEADER dosHdr =
	{
		IMAGE_DOS_SIGNATURE, // Magic number
		0, // Bytes on last page of file
		0, // Pages in file
		0, // Relocations
		0, // Size of header in paragraphs
		0, // Minimum extra paragraphs needed
		0, // Maximum extra paragraphs needed
		0, // Initial (relative) SS value
		0, // Initial SP value
		0, // Checksum
		0, // Initial IP value
		0, // Initial (relative) CS value
		0, // File address of relocation table
		0, // Overlay number
		{0, 0, 0, 0}, // Reserved words
		0, // OEM identifier (for e_oeminfo)
		0, // OEM information; e_oemid specific
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Reserved words
		sizeof(IMAGE_DOS_HEADER) // File address of new exe header
	};

	static const UInt32 peSig = IMAGE_NT_SIGNATURE;

	const IMAGE_FILE_HEADER imgFileHdr = 
	{
		IMAGE_FILE_MACHINE_I386, // Machine
		params->numSections, // NumberOfSections
		_time32(NULL), // TimeDateStamp
		0, // PointerToSymbolTable
		0, // NumberOfSymbols
		sizeof(IMAGE_OPTIONAL_HEADER32), // SizeOfOptionalHeader
		IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_RELOCS_STRIPPED | IMAGE_FILE_32BIT_MACHINE // Characteristics
	};
	
	IMAGE_OPTIONAL_HEADER32 imgOptHdr =
	{
		0x010B, // Magic
		8, // MajorLinkerVersion
		0, // MinorLinkerVersion
		0 /* TO BE FILLED IN */, // SizeOfCode
		0, // SizeOfInitializedData
		0, // SizeOfUninitializedData
		0 /* TO BE FILLED IN */, // AddressOfEntryPoint
		0 /* TO BE FILLED IN */, // BaseOfCode
		0, // BaseOfData
		0x400000, // ImageBase
		PE_PAGE_SIZE, // SectionAlignment
		PE_PAGE_SIZE, // FileAlignment
		5, // MajorOperatingSystemVersion
		0, // MinorOperatingSystemVersion
		0, // MajorImageVersion
		0, // MinorImageVersion
		4, // MajorSubsystemVersion
		0, // MinorSubsystemVersion
		0, // Win32VersionValue
		0 /* TO BE FILLED IN */, // SizeOfImage
		sizeof(IMAGE_DOS_HEADER) + 4 + sizeof(IMAGE_FILE_HEADER) +
		sizeof(IMAGE_OPTIONAL_HEADER32) + sizeof(IMAGE_SECTION_HEADER), // SizeOfHeaders
		0, // CheckSum
		IMAGE_SUBSYSTEM_WINDOWS_CUI, // Subsystem
		33088, // DllCharacteristics
		0x100000, // SizeOfStackReserve
		0x1000, // SizeOfStackCommit
		0x100000, // SizeOfHeapReserve
		0x1000, // SizeOfHeapCommit
		0, // LoaderFlags
		16, // NumberOfRvaAndSizes
		0 // DataDirectory
	};
	
	IMAGE_SECTION_HEADER sectHdr = 
	{
		{'b', 'l', 'a', 'n', 'k', '\0'}, // Name
		0 /* TO BE FILLED IN */, // VirtualSize
		0 /* TO BE FILLED IN */, // VirtualAddress
		0 /* TO BE FILLED IN */, // SizeOfRawData
		0 /* TO BE FILLED IN */, // PointerToRawData
		0, // PointerToRelocations
		0, // PointerToLinenumbers
		0, // NumberOfRelocations
		0, // NumberOfLinenumbers
		0 /* TO BE FILLED IN */ // Characteristics
	};


	fwrite(&dosHdr, sizeof(IMAGE_DOS_HEADER), 1, file);
	fwrite(&peSig, sizeof(peSig), 1, file);
	fwrite(&imgFileHdr, sizeof(IMAGE_FILE_HEADER), 1, file);

	// Update imgOptHdr
	for (i = 0, j = PE_PAGE_SIZE, s = *params->sections;
		i < params->numSections;
		++i, j += s->size, s = params->sections[i])
	{
		if (s->attr & PFSAF_EXECUTE)
		{
			imgOptHdr.SizeOfCode = s->size;
			imgOptHdr.AddressOfEntryPoint = j;
			imgOptHdr.BaseOfCode = imgOptHdr.AddressOfEntryPoint;
		}
	}

	imgOptHdr.SizeOfImage = j;

	fwrite(&imgOptHdr, sizeof(IMAGE_OPTIONAL_HEADER32), 1, file);

	// Write section headers
	for (i = 0, j = PE_PAGE_SIZE, s = *params->sections;
		i < params->numSections;
		++i, j += s->size, s = params->sections[i])
	{
		sectHdr.Misc.VirtualSize = s->size;
		sectHdr.VirtualAddress = j;
		sectHdr.SizeOfRawData = sectHdr.Misc.VirtualSize;
		sectHdr.PointerToRawData = sectHdr.VirtualAddress;
		sectHdr.Characteristics = s->attr;
		if (sectHdr.Characteristics & PFSAF_EXECUTE)
		{
			*((UInt32*)sectHdr.Name) = 'XET.';
			*((UInt32*)(sectHdr.Name + 4)) = '\0T\0\0';
		}

		fwrite(&sectHdr, sizeof(IMAGE_SECTION_HEADER), 1, file);
	}

	// Align section data by PE_PAGE_SIZE
	i = PE_PAGE_SIZE - ftell(file);
	fwrite(blankPage, i, 1, file);

	// Write section data
	for (i = 0, s = *params->sections; i < params->numSections; ++i, s = params->sections[i])
		fwrite(s->data, s->size, 1, file);
	
	//DumpPEFileInfo(file);
}

#define IsPrintable(a) ((a) >= ' ' && (a) < '~')

static void DumpData(BYTE* data, BYTE* end, unsigned int col)
{
	char buff[2] = {'0', '\0'};
	unsigned int i;


	while (data < end)
	{
		// Print data row view
		for (i = 0; i < col; ++i)
		{
			printf("%02X ", *((BYTE*)data));
			++data;

			if (data == end)
			{
				data += (col - i - 1);

				for (++i; i < col; ++i)
					printf("   ");

				break;
			}
		}

		data -= col;

		// Print ascii row view
		for (i = 0; i < col; ++i)
		{
			if (IsPrintable(*((BYTE*)data)))
				buff[0] = *((BYTE*)data);
			else
				buff[0] = '.';

			printf("%s", buff);
			++data;

			if (data == end)
				break;
		}

		putchar('\n');
	}
}

#define DumpData(a, b) DumpData(a, b, 19)

static void DumpDosHeader(IMAGE_DOS_HEADER* hdr)
{
	printf("//////////// DOS HEADER ////////////\n");
	printf("e_magic: 0x%X\n", hdr->e_magic);
	printf("e_cblp: %d\n", hdr->e_cblp);
	printf("e_cp: %d\n", hdr->e_cp);
	printf("e_crlc: %d\n", hdr->e_crlc);
	printf("e_cparhdr: %d\n", hdr->e_cparhdr);
	printf("e_minalloc: %d\n", hdr->e_minalloc);
	printf("e_maxalloc: %d\n", hdr->e_maxalloc);
	printf("e_ss: %d\n", hdr->e_ss);
	printf("e_sp: %d\n", hdr->e_sp);
	printf("e_csum: %d\n", hdr->e_csum);
	printf("e_ip: %d\n", hdr->e_ip);
	printf("e_cs: %d\n", hdr->e_cs);
	printf("e_lfarlc: %d\n", hdr->e_lfarlc);
	printf("e_ovno: %d\n", hdr->e_ovno);
	printf("e_res: {%d, %d, %d, %d}\n", hdr->e_res[0], hdr->e_res[1], hdr->e_res[2], hdr->e_res[3]);
	printf("e_oemid: %d\n", hdr->e_oemid);
	printf("e_oeminfo: %d\n", hdr->e_oeminfo);
	printf("e_res2: {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d}\n", hdr->e_res2[0], hdr->e_res2[1],
		hdr->e_res2[2], hdr->e_res2[3], hdr->e_res2[4], hdr->e_res2[5],  hdr->e_res2[6],
		hdr->e_res2[7], hdr->e_res2[8], hdr->e_res2[9]);
	printf("e_lfanew: %d\n", hdr->e_lfanew);
}

static void DumpFileHeader(IMAGE_FILE_HEADER* hdr)
{
	printf("//////////// FILE HEADER ////////////\n");
	printf("Machine: 0x%X\n", hdr->Machine);
	printf("NumberOfSections: %d\n", hdr->NumberOfSections);
	printf("TimeDateStamp: %u\n", hdr->TimeDateStamp);
	printf("PointerToSymbolTable: %u\n", hdr->PointerToSymbolTable);
	printf("NumberOfSymbols: %u\n", hdr->NumberOfSymbols);
	printf("SizeOfOptionalHeader: %d\n", hdr->SizeOfOptionalHeader);
	printf("Characteristics: 0x%X\n", hdr->Characteristics);
}

static void DumpOptionalHeader(IMAGE_OPTIONAL_HEADER* hdr)
{
	printf("//////////// OPTIONAL HEADER ////////////\n");
	printf("Magic: 0x%X\n", hdr->Magic);
	printf("MajorLinkerVersion: %d\n", hdr->MajorLinkerVersion);
	printf("MinorLinkerVersion: %d\n", hdr->MinorLinkerVersion);
	printf("SizeOfCode: %u\n", hdr->SizeOfCode);
	printf("SizeOfInitializedData: %u\n", hdr->SizeOfInitializedData);
	printf("SizeOfUninitializedData: %u\n", hdr->SizeOfUninitializedData);
	printf("AddressOfEntryPoint: %u\n", hdr->AddressOfEntryPoint);
	printf("BaseOfCode: %u\n", hdr->BaseOfCode);
	printf("BaseOfData: %u\n", hdr->BaseOfData);
	printf("ImageBase: %u\n", hdr->ImageBase);
	printf("SectionAlignment: %u\n", hdr->SectionAlignment);
	printf("FileAlignment: %u\n", hdr->FileAlignment);
	printf("MajorOperatingSystemVersion: %d\n", hdr->MajorOperatingSystemVersion);
	printf("MinorOperatingSystemVersion: %d\n", hdr->MinorOperatingSystemVersion);
	printf("MajorImageVersion: %d\n", hdr->MajorImageVersion);
	printf("MinorImageVersion: %d\n", hdr->MinorImageVersion);
	printf("MajorSubsystemVersion: %d\n", hdr->MajorSubsystemVersion);
	printf("MinorSubsystemVersion: %d\n", hdr->MinorSubsystemVersion);
	printf("Win32VersionValue: %u\n", hdr->Win32VersionValue);
	printf("SizeOfImage: %u\n", hdr->SizeOfImage);
	printf("SizeOfHeaders: %u\n", hdr->SizeOfHeaders);
	printf("CheckSum: %u\n", hdr->CheckSum);
	printf("Subsystem: %d\n", hdr->Subsystem);
	printf("DllCharacteristics: %d\n", hdr->DllCharacteristics);
	printf("SizeOfStackReserve: %u\n", hdr->SizeOfStackReserve);
	printf("SizeOfStackCommit: %u\n", hdr->SizeOfStackCommit);
	printf("SizeOfHeapReserve: %u\n", hdr->SizeOfHeapReserve);
	printf("SizeOfHeapCommit: %u\n", hdr->SizeOfHeapCommit);
	printf("LoaderFlags: %u\n", hdr->LoaderFlags);
	printf("NumberOfRvaAndSizes: %u\n", hdr->NumberOfRvaAndSizes);
}

static void DumpSectionHeader(IMAGE_SECTION_HEADER* hdr)
{
	char buff[0x100];

	memcpy(buff, hdr->Name, IMAGE_SIZEOF_SHORT_NAME);
	buff[IMAGE_SIZEOF_SHORT_NAME] = '\0';

	printf("//////////// SECTION HEADER ////////////\n");

	printf("Name: %s\n", buff);
	printf("VirtualSize: %u\n", hdr->Misc.VirtualSize);
	printf("VirtualAddress: %u\n", hdr->VirtualAddress);
	printf("SizeOfRawData: %u\n", hdr->SizeOfRawData);
	printf("PointerToRawData: %u\n", hdr->PointerToRawData);
	printf("PointerToRelocations: %u\n", hdr->PointerToRelocations);
	printf("PointerToLinenumbers: %u\n", hdr->PointerToLinenumbers);
	printf("NumberOfRelocations: %d\n", hdr->NumberOfRelocations);
	printf("NumberOfLinenumbers: %d\n", hdr->NumberOfLinenumbers);
	printf("Characteristics: 0x%X\n", hdr->Characteristics);
}


static void* ReadFileContents(FILE* file)
{
	void* data;
	unsigned int filesize;

	// Get bd->file size
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	// Get the data
	data = malloc(filesize);
	fread(data, filesize, 1, file);

	return data;
}

static void DumpPEFileInfo(FILE* peFile)
{
	unsigned int i;

	BYTE* pe = (BYTE*)ReadFileContents(peFile);

	IMAGE_DOS_HEADER* dosHdr;
	IMAGE_FILE_HEADER* imgFileHdr;
	IMAGE_OPTIONAL_HEADER* imgOptHdr;
	IMAGE_SECTION_HEADER* imgSectHdr;

	dosHdr = (IMAGE_DOS_HEADER*)pe;
	imgFileHdr = (IMAGE_FILE_HEADER*)(pe + (dosHdr->e_lfanew + 4));
	imgOptHdr = (IMAGE_OPTIONAL_HEADER*)((BYTE*)imgFileHdr + sizeof(IMAGE_FILE_HEADER));

	DumpDosHeader(dosHdr);
	putchar('\n');
	DumpFileHeader(imgFileHdr);
	putchar('\n');
	DumpOptionalHeader(imgOptHdr);
	putchar('\n');

	for (i = 0, imgSectHdr = (IMAGE_SECTION_HEADER*)((BYTE*)imgOptHdr + sizeof(IMAGE_OPTIONAL_HEADER));
		 i < imgFileHdr->NumberOfSections;
		 ++i, ++imgSectHdr)
	{
		DumpSectionHeader(imgSectHdr);

		printf("\n//////////// SECTION RAW DATA ////////////\n");

		DumpData((BYTE*)pe + imgSectHdr->PointerToRawData,
                 (BYTE*)pe + (imgSectHdr->PointerToRawData + imgSectHdr->SizeOfRawData));

		putchar('\n');
	}

	free(pe);
}
