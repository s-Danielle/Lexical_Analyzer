#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        switch (token) {
		case UKCHAR:
			output::errorUnknownChar(yytext[0]);
			break;
		case UCSTR:
			output::errorUnclosedString();
			break;
		case UDESC:
			output::errorUndefinedEscape(yytext); //check this i might be stupid
			break;
		case STRING:
			output::printToken(yylineno,token,yytext);
			break;
		default:
			output::printToken(yylineno,token,yytext);
			break;
	 }
}
    return 0;
}
