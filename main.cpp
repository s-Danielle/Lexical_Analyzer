#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>
#include <string>
void parseIllegalSeq(std::string& src, int index) {
    // we get result illegal esc seq (for printing the error) in the src parameter after we return from here
    if (src[index + 1] != 'x') {
        src = src.substr(index + 1, 1);
        return;
    }
    char next = src[index + 2], nextx2 = src[index + 3] ? src[index + 3] : '\0';
    if (next != '\"') {
        if (nextx2 != '\"') {
            src = src.substr(index + 1, 3);
            return;
        }
        src = src.substr(index + 1, 2);
        return;
    }
    src = src.substr(index + 1, 1);
}


int parse_string(std::string& source, std::string& result) {
    // this function parses the string and returns -1 if everything is ok or the index of the illegal escape sequence
    result = "";
    int checkNullindex = -1;//this is a shitty solution but in tired- in every case where we return with a num != -1 this is an error
    char current_char, next_char, hex[3];
    int ascii, index = 0;
    while (source[index]) {
        current_char = source[index];
        switch (current_char) {
        case '\"': // if we see " we continue without copying to result
            index++;
            continue;
        case '\\': //we see backslash
            if (index + 1 >= source.length()) {
                return index; //### MBU ###
                // if we see a backslash at the end of the string we return the index so we know where the error was when we atre back in main
            }
            next_char = source[index + 1]; // now we know its legal accesss and we chack what esc we have here
            if (next_char == '\0') {
                return index; // if this is zero we are in null esc and we return this index
            }
            switch (next_char) { // in all these cases we put the actual esc seq in the result
            case '\\':
                result += '\\';
                break;
            case 'n':
                result += '\n';
                break;
            case 't':
                result += '\t';
                break;
            case 'r':
                result += '\r';
                break;
            case '\"':
                result += '\"';
                break;
            case '0':
                if (checkNullindex == -1) {
                    checkNullindex = index;
                }
                break;
            case 'x':
                if (!source[index + 2] || !source[index + 3] || source[index + 2] == '\"' || source[index + 3] == '\"') {
                    return index; 
                }
                hex[0] = source[index + 2];
                hex[1] = source[index + 3];
                hex[2] = '\0';
                ascii = strtol(hex, nullptr, 16);
                if (ascii < 0x20 || ascii>0x7e) {
                    if (!((ascii == 0x09 || ascii == 0x0d) || ascii == 0x0a)) {
                        return index;
                    }
                }
                result += (char) ascii;
                index += 2;
                break;
            default:
                return index + 1;
            }
            index += 2;
            continue;
        default:
            result += current_char;
            index++;
            continue;
        }
    }
    if (checkNullindex != -1) {
        result = result.substr(0, checkNullindex - 1);
    }
    return -1;
}

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
            if (yytext[yyleng - 1] == '\"' && yytext[yyleng - 2] == '\\') { //possible hack to make sure the string doesnt end in ' \" '
                output::errorUnclosedString();
                break;
            }
            parsingStr = yytext;
            check = parse_string(parsingStr, result);
            if (check != -1) {
                parseIllegalSeq(parsingStr, check);
                output::errorUndefinedEscape(parsingStr.c_str());
                break;
            }
            output::printToken(yylineno, token, result.c_str());
            break;
        default:
            output::printToken(yylineno, token, yytext);
            break;
        }
    }
    return 0;
}
