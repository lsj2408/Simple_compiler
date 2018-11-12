#include "define.h"



int main(void)
{
	FILE* fin;
	FILE* flist;
	FILE* fout;
	if ((fin = fopen("test.txt", "r")) == NULL)
		exit(-1);
	if ((flist = fopen("16081099_list.txt", "w")) == NULL)
		exit(-1);
	if ((fout = fopen("16081099_result.txt", "w")) == NULL)
		exit(-1);

	// step1 init
	lex_cc = lex_ll = lex_ltotal = 0;
	lex_ch = lex_charcon = ' ';
	lex_sy = nosy;
	lex_number = 0;
	memset(lex_id, 0, sizeof(lex_id));
	memset(lex_line, 0, sizeof(lex_line));
	lex_setup_keywordlist();

	sleng = 0;
	stab_strindex = stab_lastindex = 0;

	// step2 insymbol

	int i, k = 0;
	char str_tmp[100];
	while (!feof(fin))
	{
		lex_insymbol(fin, flist);
		k++;
		for (i = 1; i < NKW; i++)
		{
			if (lex_ksywordlist[i] == lex_sy)
				break;
		}
		if (i < NKW)
		{
			fprintf(fout, "%d\t%s\t", k, lex_keywordlist[i]);
			if (lex_sy == ident)
				fprintf(fout, "%s\n", lex_id);
			else if (lex_sy == intcon)
				fprintf(fout, "%d\n", lex_number);
			else if (lex_sy == charcon)
				fprintf(fout, "%c\n", lex_charcon);
			else if (lex_sy == stringcon)
			{
				strncpy(str_tmp, stab + stab_lastindex, sleng);
				fprintf(fout, "%s\n", str_tmp);
			}
			else
			{
				fprintf(fout, "\n");
			}
		}
	}

	return 0;
}