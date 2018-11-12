#pragma once
#include <stdio.h>

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NKW 13+1	
#define ALNG 10+1
#define LLNG 500
#define KMAX 32
#define MIDCODEMAX 1000
#define LMAX 10
#define XMAX 2147483647
#define STMAX 100
#define SCONSTMAX 600

typedef enum symbol {
	//保留字
	constsy, intsy, charsy, voidsy, mainsy, ifsy, whilesy, switchsy, casesy, defaultsy, scanfsy, printfsy, returnsy,
	//+		-		*	/	<	  <=   >   >=   !=   ==
	plussy, minussy, multsy, divsy, lss, leq, gtr, geq, neq, eql,
	//(	     )         [       ]       {       }       ,        ;        =        :
	lparent, rparent, lbrack, rbrack, lbrace, rbrace, comma, semicolon, becomes, colon, nosy,
	//int常量	char常量	字符产常量		标识符
	intcon, charcon, stringcon, ident
}symbol;

//词法 lex

// 变量
int lex_cc, lex_ll, lex_ltotal;
char lex_ch;
symbol lex_sy;
char lex_id[ALNG];
int lex_number;
char lex_charcon;

char lex_line[LLNG];
char lex_keywordlist[NKW][ALNG];
symbol lex_ksywordlist[NKW];

// 函数
void lex_setup_keywordlist();
void lex_nextch(FILE *fin, FILE *fout);
void lex_insymbol(FILE *fin, FILE *fout);

//字符串常量表
char stab[SCONSTMAX];
int sleng;
int stab_strindex;
int stab_lastindex;