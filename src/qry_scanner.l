%{
#include <stdio.h>
#include "bima-query.h"
#include "bima-query-field.h"
#include "bima-query-table.h"
#include "qry_parser.h"
%}

%%
[sS][eE][lL][eE][cC][tT] 		return SELECT;
[fF][rR][oO][mM] 				return FROM;
[wW][hH][eE][rR][eE] 			return WHERE;
[aA][sS]						return AS;
[oO][nN]						return ON;
[jJ][oO][iI][nN]				return JOIN;
[iI][nN][nN][eE][rR]			return INNER;
[lL][eE][fF][tT]				return LEFT;
[rR][iI][gG][hH][tT]			return RIGHT;
[oO][uU][tT][eE][rR]			return OUTER;
[aA][nN][dD]					return AND;
[oO][rR]						return OR;
[gG][rR][oO][uU][pP]			return GROUP;
[bB][yY]						return BY;
[hH][aA][vV][iI][nN][gG]		return HAVING;
[oO][rR][dD][eE][rR]			return ORDER;
[aA][sS][cC]					return ASC;
[dD][eE][sS][cC]				return DESC;
[sS][uU][mM]					return SUM;
[cC][oO][uU][nN][tT]			return COUNT;
[aA][vV][gG]					return AVG;
[mM][aA][xX]					return T_MAX;
[mM][iI][nN]					return T_MIN;
[sS][tT][dD][dD][eE][vV]		return STDDEV;
[vV][aA][rR][iI][aA][cC][eE]	return VARIANCE;

[a-zA-Z0-9][a-zA-Z0-9_]*		qrylval.tkeyword = strdup(qrytext); return WORDS;
\n	;
[ \t]+	;
.	return (int) qrytext[0];
%%
