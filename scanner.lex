%{
/* C declarations */
#include "tokens.hpp"
/*our codde here*/
%}


%option yylineno
%option noyywrap

digit	([0-9])
letter	([a-zA-Z])
whitespace	([\t\n\r ])
printable              ((x[2-6][0-9A-Fa-f])|x7[0-9A-Ea-e])


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
\/\/[^\\n]*                return COMMENT;
{letter}[a-zA-Z0-9]*		 return ID;
([1-9]+{digit}*b)|0b		return NUM_B;
([1-9]+{digit}*)|0     	 return NUM;
\"([^\\\"\n\r]|\\[\\nrt0"\\]|\\x[0-9a-fA-F]{2})*\"	 return STRING;
\"([^\\\"\n\r]|\\[\\nrt0"\\]|\\x[0-9a-fA-F]{2})*  	return UCSTR;
\"([^\\\"\n\r]|\\[\\nrt0"\\]|\\x[0-9a-fA-F]{2})*\\[^\\nrt0"\\x]		return UKCHAR;
\"([^\\\"\n\r]|\\[\\nrt0"\\]|\\x[0-9a-fA-F]{2})*\\[^a-fA-F0-9]{2}.*\"  	return UDESC;
{whitespace}+		;

.		return ERROR;
