#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>

#include <iostream>


std::string& removeQuotes(std::string& input) {
    //assert(*input.begin() == *input.rbegin() == '\"');
    if (*input.rbegin() == '\"') { input.pop_back(); }
    if (*input.begin() == '\"') { input.erase(input.begin()); }
    return input;
}

std::string replaceEscSequences(const std::string& input) {
    //there is no error handling here because i count of the lexer to do this work for me.
    //assuming is correct.
    std::string result;
    result.reserve(input.length());

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '\\') {
            assert(i + 1 < input.length());
            switch (input[i + 1]) {
            case 'n': result.push_back('\n'); i++; break;
            case 'r': result.push_back('\r'); i++; break;
            case 't': result.push_back('\t'); i++; break;
            case '\\': result.push_back('\\'); i++; break;
            case '"': result.push_back('"'); i++; break;
            case '0': return result;
            case 'x':
                assert(i + 3 < input.length());
                std::string hex = input.substr(i + 2, 2); // \xdd, need to skip both 'x' and '\'
                i += 3; // the loops adds one more anyway!
                char c = static_cast<char>(std::stoi(hex, nullptr, 16)); // turns out stoi knows how to do this
                result.push_back(c);
            }
        }
        else {
            result.push_back(input[i]);
        }
    }
    return result;
}
int main() {
    enum tokentype token;
    std::string parsingStr;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        auto seq = &yytext[yyleng - 1];
        switch (token) {
        case UKCHAR:
            output::errorUnknownChar(yytext[yyleng - 1]);
            break;
        case UCSTR:
            output::errorUnclosedString();
            break;
        case UDESC:
            output::errorUndefinedEscape(yytext + (yyleng - 1));
            break;
        case ILLHEX:
            for (; *seq != 'x'; seq--);
            output::errorUndefinedEscape(seq);
            break;
        case STRING:
            parsingStr = std::string(yytext);
            removeQuotes(parsingStr);
            parsingStr = replaceEscSequences(parsingStr);
            // std::cout << parsingStr << '\n';
            output::printToken(yylineno, token, parsingStr.c_str());
            break;
        default:
            output::printToken(yylineno, token, yytext);
            break;
        }
    }
    return 0;
}
