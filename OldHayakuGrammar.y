%{
#include "common.h"
#include <stdio.h>
#include <string.h>

unsigned int lineNumber;

void yyerror(const char* msg);
%}

%union
{
	int   s;
	int   s32;
	short s16;
	char  s8;
	
	unsigned int   u;
	unsigned int   u32;
	unsigned short u16;
	unsigned char  u8;
	
	float f;
	
	float f32;
	double f64;
}

%token IDENTIFIER

%token STR_LIT
%token ASCII_LIT
%token UTF8_LIT
%token UTF16_LIT
%token UTF32_LIT

%token <s> INT_LIT
%token <u> UINT_LIT
%token <f> FLOAT_LIT

%token KEY_INT
%token KEY_INT32
%token KEY_INT16
%token KEY_INT8

%token KEY_UINT
%token KEY_UINT32
%token KEY_UINT16
%token KEY_UINT8

%token KEY_FLOAT
%token KEY_FLOAT32
%token KEY_FLOAT64

%token KEY_IMPORT
%token KEY_SIZEOF
%token KEY_DEFINE
%token KEY_REGISTER
%token KEY_STATIC
%token KEY_TYPEDEF
%token KEY_CONST
%token KEY_VOLATILE

%right '='
%left '+' '-'
%left '*' '/'
%%

translation_unit : extern_declaration                  { printf("BISON: translation_unit -> extern_declaration\n"); }
                 | translation_unit extern_declaration { printf("BISON: translation_unit -> translation_unit extern_declaration\n"); }
;

extern_declaration : func_def {}
            | declaration     {}
;

/* func_def : */

declaration : declaration_specifiers init_declaration_list ';' {}
;

declaration_specifiers : /* empty */                        {}
                | storage_specifier declaration_specifiers  {}
                | type_specifier declaration_specifier      {}
                | type_qualifier declaration_specifier {}
;

storage_specifier : KEY_REGISTER {}
                  | KEY_STATIC   {}
                  | KEY_TYPEDEF  {}
;

type_specifier : KEY_INT     {}
               | KEY_INT32   {}
               | KEY_INT16   {}
               | KEY_INT8    {}
               | KEY_UINT    {}
               | KEY_UINT32  {}
               | KEY_UINT16  {}
               | KEY_UINT8   {}
               | KEY_FLOAT   {}
               | KEY_FLOAT32 {}
               | KEY_FLOAT64 {}
               | typedef_name {}
;

type_qualifier : KEY_CONST    {}
               | KEY_VOLATILE {}
;

type_qualifier_list : type_specifier type_qualifier_list {}
                    | type_specifier                     {}
                    | type_qualifier type_qualifier_list {}
                    | type_qualifier                     {}
;

typedef_name : IDENTIFIER {}
;

init_declaration_list : init_declaration {}
               | init_declaration_list ',' init_declaration
;

init_declaration : declaration {}
          | declaration '=' init {}
;

init : assign_expr   {}
     | '{' init_list '}' {}
;

init_list : init {}
          | init_list init {}
;

expr : assign_expr          {}
     | expr ',' assign_expr {}
;

assign_expr : conditional_expr {}
            | unary_expr assign_op assign_expr {}
;

conditional_expr : logical_or_expr {}
                 | logical_or_expr '?' expr ':' conditional_expr {}
;

logical_or_expr : logical_and_expr {}
                | logical_or_expr '|' '|' logical_and_expr {}
;

logical_and_expr : inclusive_or_expr {}
                 | logical_and_expr '&' '&' inclusive_or_expr {}
;

inclusive_or_expr : exclusive_or_expr {}
                  | inclusive_or_expr '|' exclusive_or_expr {}
;

exclusive_or_expr : and_expr {}
                  | exclusive_or_expr '^' and_expr
;

and_expr : equality_expr {}
         | and_expr '&' equality_expr {}
;

equality_expr : relational_expr {}
              | equality_expr '==' relational_expr {}
              | equality_expr '!=' relational_expr {}
;

relational_expr : shift_expr {}
                | relational_expr '<' shift_expr {}
                | relational_expr '>' shift_expr {}
                | relational_expr '<=' shift_expr {}
                | relational_expr '>=' shift_expr {}
;

shift_expr : add_expr {}
           | shift_expr '<<' add_expr {}
           | shift_expr '>>' add_expr {}
;

add_expr : mult_expr {}
         | add_expr '+' mult_expr {}
         | add_expr '-' mult_expr {}
;

mult_expr : cast_expr {}
          | mult_expr '*' cast_expr {}
          | mult_expr '/' cast_expr {}
          | mult_expr '%' cast_expr {}
;

cast_expr : unary_expr {}
          | '(' type_name ')' cast_expr {}
;

type_name : type_qualifier_list abstract_declarator {}
          | type_qualifier_list /* empty */ {}
;


unary_expr : postfix_expr                 {}
           | '++' unary_expr              {}
           | '--' unary_expr              {}
           | unary_op cast_expr           {}
           | KEY_SIZEOF unary_expr        {}
           | KEY_SIZEOF '(' type_name ')' {}
;

unary_op : '&' {}
         | '*' {}
         | '+' {}
         | '-' {}
         | '~' {}
         | '!' {}
;


postfix_expr : primary_expr                       {}
             | postfix_expr '[' expr ']'          {} /* array */
             | postfix_expr '(' arg_expr_list ')' {} /* function call */
             | postfix_expr '(' ')'               {} /* function call with no args */
             | postfix_expr '.' IDENTIFIER        {} /* struct member access */
             | postfix_expr '->' IDENTIFIER       {} /* struct pointer member access */
             | postfix_expr '++'                  {} /* post increment */
             | postfix_expr '--'                  {} /* post decrement */
;

primary_expr : IDENTIFIER   {}
             | INT_LIT      {}
             | UINT_LIT     {}
             | FLOAT_LIT    {}
             | string_lit   {}
             | '(' expr ')' {}
;



string_lit : STR_LIT   {}
           | ASCII_LIT {}
           | UTF8_LIT  {}
           | UTF16_LIT {}
           | UTF32_LIT {}
;

pointer : '*' type_qualifier_list         {}
        | '*'                             {}
        | '*' type_qualifier_list pointer {}
        | '*' pointer                     {}
;

declarator : pointer direct_declarator {}
           | direct_declarator         {}
;

direct_declarator : IDENTIFIER                                {}
                  | '(' declarator ')'                        {}
                  | direct_declarator '[' constant_expr ']'   {}
                  | direct_declarator '(' param_type_list ')' {}
                  | direct_declarator '[' ']'                 {}





/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

statement : expr_statement   { printf("BISON: statement -> expr_statement\n"); }
          | import_statement { printf("BISON: statement -> import_statement\n"); }
          | define_statement { printf("BISON: statement -> define_statement\n"); }
;

expr_statement : expr {}
;

import_statement : KEY_IMPORT string_lit {}
;

define_statement : KEY_DEFINE IDENTIFIER '=' UINT_LIT  {}
                 | KEY_DEFINE IDENTIFIER '=' INT_LIT   {}
                 | KEY_DEFINE IDENTIFIER '=' FLOAT_LIT {}
;

expr : INT_LIT       { printf("BISON: expr -> INT_LIT (%d)\n", $1); }
     | UINT_LIT      { printf("BISON: expr -> UINT_LIT (%u)\n", $1); }
     | FLOAT_LIT     { printf("BISON: expr -> FLOAT_LIT (%f)\n", $1); }
     | expr '+' expr { printf("BISON: expr -> expr '+' expr\n"); }
     | expr '-' expr { printf("BISON: expr -> expr '-' expr\n"); }
     | expr '/' expr { printf("BISON: expr -> expr '/' expr\n"); }
     | expr '*' expr { printf("BISON: expr -> expr '*' expr\n"); }
     | '(' expr ')'  { printf("BISON: expr -> '(' expr ')'\n"); }
;

%%
#include "lex.yy.c"
