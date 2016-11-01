#pragma once

#define _CRT_SECURE_NO_WARNINGS

// Platform
#ifdef _MSC_VER
	#define WIN32
	#define _CRT_SECURE_NO_WARNINGS
#else
	#define LINUX
#endif

// Endian
#if defined (__hppa__) || defined (__m68k__) || defined (mc68000) || defined (_M_M68K) || (defined (__MIPS__) && defined (__MISPEB__)) || defined (__ppc__) || defined (__POWERPC__) || defined (_M_PPC) || defined (__sparc__)
	#ifndef BIG_ENDIAN
		#define BIG_ENDIAN
	#endif
#else
	#ifndef LITTLE_ENDIAN
		#define LITTLE_ENDIAN
	#endif
#endif

#ifdef _DEBUG
#define DEBUG
#endif