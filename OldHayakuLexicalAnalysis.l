%{
/* The value that yylex returns must be the positive numeric code 
for the type of token it has just found; a zero or negative value 
signifies end-of-input. */

void PrintLexeme();
%}

%option noyywrap

white_space   [ \t]*
digit         [0-9]
alpha         [a-zA-Z_]
delim         [;]

strlit        \"[^\"\r\n]*\"
asciilit      "ascii"{strlit}
utf8lit       "utf8"{strlit}
utf16lit      "utf16"{strlit}
utf32lit      "utf32"{strlit}

identifier    {alpha}+({alpha}|{digit})*

num           -{digit}+
int           -{num}
uint          {num}
float         -?{digit}+(\.{digit}+)?)|(\.{digit}+

%%

{int}         { sscanf(yytext, "%d", &yylval); printf("FLEX : INT_LIT (%d)\n", yylval); return INT_LIT; }
{uint}        { sscanf(yytext, "%u", &yylval); printf("FLEX : UINT_LIT (%u)\n", yylval); return UINT_LIT; }
{float}       { sscanf(yytext, "%lf", &yylval); printf("FLEX : FLOAT_LIT (%g)\n", yylval); return FLOAT_LIT; }

{strlit}      { printf("FLEX : STR_LIT (%s)\n", yytext); return STR_LIT; }
{asciilit}    { printf("FLEX : ASCII_LIT (%s)\n", yytext); return ASCII_LIT; }
{utf8lit}     { printf("FLEX : UTF8_LIT\n"); return UTF8_LIT; }
{utf16lit}    { printf("FLEX : UTF16_LIT\n"); return UTF16_LIT; }
{utf32lit}    { printf("FLEX : UTF32_LIT\n"); return UTF32_LIT; }

"UInt"        { printf("FLEX : UINT_KEY\n"); return UINT_KEY; }
"UInt32"      { printf("FLEX : UINT32_KEY\n"); return UINT32_KEY; }
"UInt16"      { printf("FLEX : UINT16_KEY\n"); return UINT16_KEY; }
"UInt8"       { printf("FLEX : UINT8_KEY\n"); return UINT8_KEY; }

"Int"         { printf("FLEX : INT_KEY\n"); return INT_KEY; }
"Int32"       { printf("FLEX : INT32_KEY\n"); return INT32_KEY; }
"Int16"       { printf("FLEX : INT16_KEY\n"); return INT16_KEY; }
"Int8"        { printf("FLEX : INT8_KEY\n"); return INT8_KEY; }

"Float"       { printf("FLEX : FLOAT_KEY\n"); return FLOAT_KEY; }
"Float64"     { printf("FLEX : FLOAT64_KEY\n"); return FLOAT64_KEY; }
"Float32"     { printf("FLEX : FLOAT32_KEY\n"); return FLOAT32_KEY; }

"import"      { printf("FLEX : KEY_IMPORT\n"); return KEY_IMPORT; }
"define"      { printf("FLEX : KEY_DEFINE\n"); return KEY_DEFINE; }
"register"    { printf("FLEX : KEY_REGISTER\n"); return KEY_REGISTER; }
"static"      { printf("FLEX : KEY_STATIC\n"); return KEY_STATIC; }
"typedef"     { printf("FLEX : KEY_TYPEDEF\n"); return KEY_TYPEDEF; }
"const"       { printf("FLEX : KEY_CONST\n"); return KEY_CONST; }
"volatile"    { printf("FLEX : KEY_VOLATILE\n"); return KEY_VOLATILE; }
"sizeof"      { printf("FLEX : KEY_SIZEOF\n"); return KEY_SIZEOF; }

{identifier}  { printf("FLEX : IDENTIFIER\n"); return IDENTIFIER; }

";"           { printf("FLEX : EOS (;)\n"); return ';'; }
"?"           { printf("FLEX : OPERATOR ?\n"); return '?'; }
"|"           { printf("FLEX : OPERATOR |\n"); return '|'; }
","           { printf("FLEX : OPERATOR ,\n"); return ','; }
":"           { printf("FLEX : OPERATOR :\n"); return ':'; }
"&"           { printf("FLEX : OPERATOR &\n"); return '&'; }
"~"           { printf("FLEX : OPERATOR ~\n"); return '~'; }

"<="          { printf("FLEX : OPERATOR <=\n"); return '<='; }
">="          { printf("FLEX : OPERATOR >=\n"); return '>='; }
"<"           { printf("FLEX : OPERATOR <\n"); return '<'; }
">"           { printf("FLEX : OPERATOR >\n"); return '>'; }
"!="          { printf("FLEX : OPERATOR !=\n"); return '!='; }
"=="          { printf("FLEX : OPERATOR ==\n"); return '=='; }

"="           { printf("FLEX : OPERATOR =\n"); return '='; }

">>"          { printf("FLEX : OPERATOR >>\n"); return '>>'; }
"<<"          { printf("FLEX : OPERATOR <<\n"); return '<<'; }

"*"           { printf("FLEX : OPERATOR *\n"); return '*'; }
"*="          { printf("FLEX : OPERATOR *=\n"); return '*='; }
"/"           { printf("FLEX : OPERATOR /\n"); return '/'; }
"/="          { printf("FLEX : OPERATOR /=\n"); return '/='; }
"%"           { printf("%s", "FLEX : OPERATOR %\n"); return '%'; }
"%="          { printf("%s", "FLEX : OPERATOR %=\n"); return '%='; }

"+"           { printf("FLEX : OPERATOR +\n"); return '+'; }
"+="          { printf("FLEX : OPERATOR +=\n"); return '+='; }
"-"           { printf("FLEX : OPERATOR -\n"); return '-'; }
"-="          { printf("FLEX : OPERATOR -=\n"); return '-='; }
"++"          { printf("FLEX : OPERATOR ++\n"); return '++'; }
"--"          { printf("FLEX : OPERATOR --\n"); return '--'; }

"{"           { printf("FLEX : BEGBRACE\n"); return '{'; }
"}"           { printf("FLEX : ENDBRACE\n"); return '}'; }
"("           { printf("FLEX : BEGPAREN\n"); return '('; }
")"           { printf("FLEX : ENDPAREN\n"); return ')'; }

\n            { printf("FLEX : NEWLINE\n"); ++lineNumber; }
{white_space} { printf("FLEX : ws\n"); }

<<EOF>>       { printf("FLEX : EOF\n"); return 0; }
.             { yyerror("Illegal input"); }

%%

void yyerror(const char *msg)
{
	if (*yytext == 0)
		fprintf(stderr, "Error on line %d: %s (Null character)\n", lineNumber, msg);
	else
		fprintf(stderr, "Error on line %d: %s\n", lineNumber, msg);
}