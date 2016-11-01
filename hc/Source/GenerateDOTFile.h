#pragma once
#include "ParseNode.h"
#include "Symbol.h"
#include "ICode.h"

void GenerateDOTFile(struct FunctionTable* ft, struct SymbolTable* gst, const char* filePath);
