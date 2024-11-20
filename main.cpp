#include "tokens.hpp"
#include "output.hpp"

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        switch (token) {
		case UKCHAR:
			output::errorUnknownChar(*yytext);
			break;
		case UCSTR:
			output::errorUnclosedString();
		case UDESC:
			output::errorUndefinedEscape(yytext); //check this i might be stupid
		deafault:
			output::printToken(yylineno,token,yytext);
			break;
	 }
}
    return 0;
}
