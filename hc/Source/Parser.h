#pragma once

void SetParserFunctionTable(struct FunctionTable* ft);
struct FunctionTable* GetParserFunctionTable();
void SetParserGlobalSymbolTable(struct SymbolTable* gst);
void SetParserCurrentFunction(struct Function* f);