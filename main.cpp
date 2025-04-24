#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>
#include <string>


int main() {
    enum tokentype token;
    std::string parsingStr = "", result = "";
    int check;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        switch (token) {
        case UKCHAR:
            output::errorUnknownChar(yytext[yyleng - 1]);
            break;
        case UCSTR:
            output::errorUnclosedString();
            break;
        case UDESC:
            output::errorUndefinedEscape(&yytext[yyleng - 1]); //check this i might be stupid
            break;
        case STRING:
            
            output::printToken(yylineno, token, result.c_str());
            break;
        default:
            output::printToken(yylineno, token, yytext);
            break;
        }
    }
    return 0;
}
