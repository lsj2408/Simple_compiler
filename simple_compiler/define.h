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
	//������
	constsy, intsy, charsy, voidsy, mainsy, ifsy, whilesy, switchsy, casesy, defaultsy, scanfsy, printfsy, returnsy,
	//+		-		*	/	<	  <=   >   >=   !=   ==
	plussy, minussy, multsy, divsy, lss, leq, gtr, geq, neq, eql,
	//(	     )         [       ]       {       }       ,        ;        =        :
	lparent, rparent, lbrack, rbrack, lbrace, rbrace, comma, semicolon, becomes, colon, nosy,
	//int����	char����	�ַ�������		��ʶ��
	intcon, charcon, stringcon, ident
}symbol;

//�ʷ� lex

// ����
int lex_cc, lex_ll, lex_ltotal;
char lex_ch;
symbol lex_sy;
char lex_id[ALNG];
int lex_number;
char lex_charcon;

char lex_line[LLNG];
char lex_keywordlist[NKW][ALNG];
symbol lex_ksywordlist[NKW];

// ����
void lex_setup_keywordlist();
void lex_nextch(FILE *fin, FILE *fout);
void lex_insymbol(FILE *fin, FILE *fout);

//�ַ���������
char stab[SCONSTMAX];
int sleng;
int stab_strindex;
int stab_lastindex;