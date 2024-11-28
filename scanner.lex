%{
/* C declarations */
#include "tokens.hpp"
char string_input[1024];
int string_index;
/*our code here*/
%}


%option yylineno
%option noyywrap

digit	([0-9])
letter	([a-zA-Z])
whitespace	([\t\n\r ])
printableHex              (\x20-\x7e)

%x STR_STATE

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
\" 		{BEGIN(STR_STATE); memset(string_input,0,1024); string_index=0; }
<STR_STATE>\"		{string_input[string_index++]='\0'; BEGIN(INITIAL); return STRING;	}
<STR_STATE>\\n	         string_input[string_index++]='\n';
<STR_STATE>\\t		 string_input[string_index++]='\t';
<STR_STATE>\\r 		 string_input[string_index++]='\r';
<STR_STATE>\\\\ 	 string_input[string_index++]='\\';
<STR_STATE>\\\" 	 string_input[string_index++]='\"';
<STR_STATE>\\0		;
<STR_STATE>(printable)		{string_input[0]=yytext[0]; string_input[1]='\0';}
<STR_STATE>\\x[0-9a-fA-F]{2} {
                    char hex[3] = { yytext[2], yytext[3], '\0' }; 
                    int asciiValue = strtol(hex, NULL, 16);
                    if (asciiValue >= 0x20 && asciiValue <= 0x7E) {
                        char c = (char)asciiValue;
                 	string_input[string_index++]=c;   
		} else {
                    BEGIN(INITIAL);
                    memcpy(string_input,yytext,yyleng);
					return UDESC; // Invalid printable character
                    }
}
<STR_STATE>\\x[^\n] { 
			BEGIN(INITIAL);
            memcpy(string_input,yytext,yyleng);
			return UDESC;	
			
		}
<STR_STATE>[\n\t\r]	{
			BEGIN(INITIAL);
			return UCSTR;
		}
<STR_STATE>\\.		{
			BEGIN(INITIAL);
            memcpy(string_input,yytext,yyleng);
			return UDESC;
		}


{whitespace}+		;

.		{
        memcpy(string_input,yytext,yyleng);
        return UKCHAR;}
