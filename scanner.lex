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
printableHex              (\x20-\x7e)



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
\"[ a-zA-z0-9]*\"		return STRING;		
{whitespace}+		;

.		{ return UDESC; }

