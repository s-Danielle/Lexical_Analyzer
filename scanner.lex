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
legalEsc           ([\\ntr\"0])
hex              (x[0-9A-Fa-f]{0,2})
legalStr           ([ !#-\[\]-~	])


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
= 	 return ASSIGN;
[!=><]=|>|<             return RELOP;
[\-+\*\/]                  return BINOP;
\/\/[^\n\r]*                return COMMENT;
{letter}[a-zA-Z0-9]*		 return ID;
([1-9]+{digit}*b)|0b		return NUM_B;
([1-9]+{digit}*)|0     	 return NUM;
\"({legalStr}|\\{legalEsc}|\\{hex})*\"			 return STRING;
\"({legalStr}|\\{legalEsc}|\\{hex})*			 return UCSTR;
\"({legalStr}|\\{legalEsc}|\\{hex})*\\[^\\ntr\"0]	         return UDESC;
{whitespace}+		;

.		{ return UKCHAR; }

