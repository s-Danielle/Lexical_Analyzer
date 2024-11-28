#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>
#include <string>
#include <regex>
extern char string_input[1024];
int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        switch (token) {
		case UKCHAR:
			output::errorUnknownChar(string_input[0]);
			break;
		case UCSTR:
			output::errorUnclosedString();
			break;
		case UDESC:
			output::errorUndefinedEscape(string_input); //check this i might be stupid
			break;
		case STRING:
			output::printToken(yylineno,token,string_input);
			break;
		default:
			output::printToken(yylineno,token,yytext);
			break;
	 }
}
    return 0;
}
