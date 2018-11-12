#include "define.h"

#define LEX_CH_ALPHABET ((lex_ch >= 'a' && lex_ch <= 'z') || (lex_ch >= 'A' && lex_ch <= 'Z') || (lex_ch == '_'))
#define LEX_CH_NUMBER ((lex_ch >= '0') && (lex_ch <= '9'))
#define LEX_CH_CHARCON_AM ((lex_ch == '+') || (lex_ch == '-') || (lex_ch == '*') || (lex_ch == '/'))

void lex_setup_keywordlist()
{
	strcpy(lex_keywordlist[1], "case      ");
	strcpy(lex_keywordlist[2], "char      ");
	strcpy(lex_keywordlist[3], "const     ");
	strcpy(lex_keywordlist[4], "default   ");
	strcpy(lex_keywordlist[5], "if        ");
	strcpy(lex_keywordlist[6], "int       ");
	strcpy(lex_keywordlist[7], "main      ");
	strcpy(lex_keywordlist[8], "printf    ");
	strcpy(lex_keywordlist[9], "return    ");
	strcpy(lex_keywordlist[10], "scanf     ");
	strcpy(lex_keywordlist[11], "switch    ");
	strcpy(lex_keywordlist[12], "void      ");
	strcpy(lex_keywordlist[13], "while     ");

	

	lex_ksywordlist[1] = casesy;
	lex_ksywordlist[2] = charsy;
	lex_ksywordlist[3] = constsy;
	lex_ksywordlist[4] = defaultsy;
	lex_ksywordlist[5] = ifsy;
	lex_ksywordlist[6] = intsy;
	lex_ksywordlist[7] = mainsy;
	lex_ksywordlist[8] = printfsy;
	lex_ksywordlist[9] = returnsy;
	lex_ksywordlist[10] = scanfsy;
	lex_ksywordlist[11] = switchsy;
	lex_ksywordlist[12] = voidsy;
	lex_ksywordlist[13] = whilesy;
}

void lex_error(FILE *fin, FILE *fout) //todo
{
	printf("error line: %d column: %d", lex_ltotal, lex_cc);
	//todo
}

void lex_nextch(FILE *fin, FILE *fout)
{
	char ch = ' ';
	if (lex_cc == lex_ll)
	{
		if (feof(fin) > 0)
		{
			fprintf(fout, "program incomplete");
			return;
		}
		//todo: error
		lex_ll = 0;
		lex_cc = 0;

		while (lex_ll == 0)
		{
			while ((ch = fgetc(fin)) != '\n')
			{
				if (ch == EOF)
					return;
				lex_line[lex_ll] = ch;
				lex_ll++;
				fputc(ch, fout);

			}
		}
		lex_ltotal++;
	}
	lex_ch = lex_line[lex_cc++];
}

void lex_insymbol(FILE *fin, FILE *fout)
{
	int lex_id_index = 0;
	int lex_id_bsearch_i = 0, lex_id_bsearch_j = 0;
label_1:
	while (lex_ch == ' ' || lex_ch == 9)
		lex_nextch(fin, fout);
	if (isalpha(lex_ch) || (lex_ch == '_'))
	{
		lex_id_index = 0;
		strcpy(lex_id, "          ");
		do
		{
			if (lex_id_index < ALNG - 1)
			{
				lex_id[lex_id_index++] = lex_ch;
			}
			lex_id[ALNG - 1] = '\0';
			lex_nextch(fin, fout);
		} while (isalnum(lex_ch) || (lex_ch == '_'));
		lex_id_bsearch_i = 1;
		lex_id_bsearch_j = NKW;
		do
		{
			lex_id_index = (lex_id_bsearch_i + lex_id_bsearch_j) / 2;
			if (strcmp(lex_id, lex_keywordlist[lex_id_index]) <= 0)
				lex_id_bsearch_j = lex_id_index - 1;
			if (strcmp(lex_id, lex_keywordlist[lex_id_index]) >= 0)
				lex_id_bsearch_i = lex_id_index + 1;
		} while (lex_id_bsearch_i <= lex_id_bsearch_j);
		if (lex_id_bsearch_i - 1 > lex_id_bsearch_j)
			lex_sy = lex_ksywordlist[lex_id_index];
		else
			lex_sy = ident;
	}
	else if (isdigit(lex_ch))
	{
		int lex_num_k, lex_num_mresult = 0;
		lex_sy = intcon;
		lex_number = 0;
		if (lex_ch == '0')
		{
			lex_nextch(fin, fout);
			if (isdigit(lex_ch))
			{
				while (isdigit(lex_ch))
					lex_nextch(fin, fout);
				lex_error(fin, fout);
			}
		}
		else
		{
			lex_num_k = 1;
			lex_num_mresult = lex_ch - '0';
			lex_nextch(fin, fout);
			while (isdigit(lex_ch))
			{
				lex_num_k++;
				lex_num_mresult = lex_num_mresult * 10 + lex_ch - '0';
				lex_nextch(fin, fout);
			}
			lex_number = lex_num_mresult;
			if (lex_number > XMAX)
				lex_error(fin, fout);
		}
	}
	else if (lex_ch == '\'')
	{
		lex_sy = charcon;
		lex_charcon = ' ';
		lex_nextch(fin, fout);
		if (((LEX_CH_CHARCON_AM) || isalpha(lex_ch) || isdigit(lex_ch) || (lex_ch == '_')))
		{
			lex_charcon = lex_ch;
			lex_nextch(fin, fout);
			if (lex_ch != '\'')
			{
				lex_error(fin, fout);
				lex_sy = nosy;
				goto label_1;
			}
			else
				lex_nextch(fin, fout);
		}
		else
		{
			lex_error(fin, fout);
			lex_sy = nosy;
			goto label_1;
		}
	}
	else if (lex_ch == '\"')
	{
		int lex_stringcon_k = 0;

		//memset(stab, 0, sizeof(stab));
	label_2:
		lex_nextch(fin, fout);
		if (lex_ch == '\"')
			goto label_3;

		if (lex_ch >= 32 && lex_ch <= 126 && lex_ch != 34)
		{
			stab[stab_strindex + lex_stringcon_k] = lex_ch;
			lex_stringcon_k++;
			goto label_2;
		}
		else
		{
			lex_error(fin, fout);
			goto label_1;
		}
	label_3:
		lex_sy = stringcon;
		stab_lastindex = stab_strindex;
		sleng = lex_stringcon_k;
		stab_strindex += lex_stringcon_k;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '=')
	{
		lex_nextch(fin, fout);
		if (lex_ch == '=')
		{
			lex_sy = eql;
			lex_nextch(fin, fout);
		}
		else
			lex_sy = becomes;
	}
	else if (lex_ch == '>')
	{
		lex_nextch(fin, fout);
		if (lex_ch == '=')
		{
			lex_sy = geq;
			lex_nextch(fin, fout);
		}
		else
			lex_sy = gtr;
	}
	else if (lex_ch == '<')
	{
		lex_nextch(fin, fout);
		if (lex_ch == '=')
		{
			lex_sy = leq;
			lex_nextch(fin, fout);
		}
		else
			lex_sy = lss;
	}
	else if (lex_ch == '!')
	{
		lex_nextch(fin, fout);
		if (lex_ch == '=')
		{
			lex_sy = neq;
			lex_nextch(fin, fout);
		}
		else
		{
			lex_error(fin, fout);
			lex_sy = nosy;
			goto label_1;
		}
	}
	else if (lex_ch == '+')
	{
		lex_sy = plussy;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '-')
	{
		lex_sy = minussy;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '*')
	{
		lex_sy = multsy;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '/')
	{
		lex_sy = divsy;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == ',')
	{
		lex_sy = comma;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == ':')
	{
		lex_sy = colon;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == ';')
	{
		lex_sy = semicolon;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '(')
	{
		lex_sy = lparent;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == ')')
	{
		lex_sy = rparent;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '[')
	{
		lex_sy = lbrack;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == ']')
	{
		lex_sy = rbrack;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '{')
	{
		lex_sy = lbrace;
		lex_nextch(fin, fout);
	}
	else if (lex_ch == '}')
	{
		lex_sy = rbrace;
		lex_nextch(fin, fout);
	}
	else
	{
		return;
		lex_sy = nosy;
		lex_error(fin, fout);
		lex_nextch(fin, fout);
		goto label_1;
	}
}