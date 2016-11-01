#pragma once
#include "Common.h"
#include <stdio.h>
#include "ICode.h"


void Link(FILE* exeFile, struct FunctionTable* ft, const char* entryPoint);
