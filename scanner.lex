%{
/* C declarations */
#include "tokens.hpp"


/*our code here*/
%}


%option yylineno
%option noyywrap

digit	([0-9])
letter	([a-zA-Z])
whitespace	([\t\n\r ])
printableCharHex		   ([2-6][0-9a-fA-F]|7[0-9a-eA-E]|0[9AaDd])
legalEsc           (\\[\\ntr\"0]|\\x{printableCharHex})
simpleStrChar           ([ !#-\[\]-~	])
legalStrContent			({simpleStrChar}|{legalEsc})*


%%


void		return VOID;
int   	 return INT;
byte   	return BYTE;
bool  	 return BOOL;
and   	 return AND;
or   	  return OR;
not    return NOT;
true 	  return TRUE;
false	  return FALSE;
return     return RETURN;
if   	 return IF;
else 	 return ELSE;
while	 return WHILE;
break	 return BREAK;
continue      return CONTINUE;
;     return SC;
,     return COMMA;
\(    return LPAREN;
\)       return RPAREN;
\{       return LBRACE;
\}       return RBRACE;
\[       return LBRACK;
\]       return RBRACK;
= 	 return ASSIGN;
[!=><]=|>|<             return RELOP;
[\-+\*\/]                  return BINOP;
\/\/[^\n\r]*                return COMMENT;
{letter}[a-zA-Z0-9]*		 return ID;
([1-9]+{digit}*b)|0b		return NUM_B;
([1-9]+{digit}*)|0     	 return NUM;
\"{legalStrContent}\"			 return STRING;
\"{legalStrContent}			 return UCSTR;
\"{legalStrContent}\\x[^\"\n]{0,2}         return UDESC;
\"{legalStrContent}\\[^\\ntr\"0x]	         return UDESC;

{whitespace}+		;

.		{ return UKCHAR; }

