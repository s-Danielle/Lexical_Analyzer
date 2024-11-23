#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>
#include <string>

void handleString(std::string str, int len){
	
}

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    std::string temp;
    while ((token = static_cast<tokentype>(yylex()))) {
        switch (token) {
		case UKCHAR:
			output::errorUnknownChar(yytext[yyleng-1]);
			break;
		case UCSTR:
			output::errorUnclosedString();
			break;
		case UDESC:
			output::errorUndefinedEscape(yytext); //check this i might be stupid
			break;
		case STRING:
			temp = yytext;
			handleString(temp, yyleng);
			output::printToken(yylineno,token,temp.c_str());
			break;
		default:
			output::printToken(yylineno,token,yytext);
			break;
	 }
}
    return 0;
}
