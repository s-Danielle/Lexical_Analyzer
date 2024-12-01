#include "tokens.hpp"
#include "output.hpp"
#include <cstdio>
#include <string>
 
	
void parseIllegalSeq(std::string &src, int index){
    if (src[index+1]!='x'){
        src = src.substr(index + 1, 1);
        return;
    }
    char next=src[index+2], nextx2=src[index+3]?src[index+3]:'\0';
    if (((next>='a'&&next<='z')||(next>='A'&&next<='Z'))||(next>='0'&&next<='9')){
        if (((nextx2>='a'&&nextx2<='z')||(nextx2>='A'&&nextx2<='Z'))||(nextx2>='0'&&nextx2<='9')){
            src = src.substr(index + 1, 3);
            return;
        }
        src = src.substr(index + 1, 2);
        return;
    }
    src = src.substr(index + 1, 1);
}

//on success return -1, on failure returns index of illegal seq in src 
int parse_string(std::string &source, std::string &result){
	result="";
	char current_char, next_char, hex[3];
	int ascii, index=0;
	while(source[index]){
		current_char=source[index];
		switch (current_char) {
			case '\"':
				//ignore in beginning and end " ", if we didn't handle input case of " hi \" this is where we check end for uncstr
				index++;
				continue;
			case '\\':
				if (index + 1 >= source.length()) {
					return index;
				}
				next_char = source[index + 1];
				if (!next_char) {
					return index;
					// we shouldn't get here but if we do its uncstr
				 }
				switch (next_char) {
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
						result+'\0';
						break;
					case 'x':
						if (!source[index + 2] || !source[index + 3]) {
							return index + 1;
						}
						hex[0] = source[index + 2];
						hex[1] = source[index + 3];
						hex[2] = '\0';
						ascii = strtol(hex, nullptr, 16);
						//todo add illegal seq
						 if (ascii<0x20 || ascii>0x7e){
							 return index;
						 }
						 result += (char) ascii;
						 index+=2;
						 break;
					 default:
			 			return index + 1;
					 }
				index += 2;
	 			continue;
	 		default: 
				result+=current_char;
				index++;
				continue;
		}
	}
	return -1;
}

int main() {
    enum tokentype token;
    std::string parsingStr="", result="";
    int check;
    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        switch (token) {
		case UKCHAR:
			output::errorUnknownChar(yytext[yyleng-1]);
			break;
		case UCSTR:
			output::errorUnclosedString();
			break;
		case UDESC:
			output::errorUndefinedEscape(&yytext[yyleng-1]); //check this i might be stupid
			break;
		case STRING:
			if (yytext[yyleng-1]=='\"'&& yytext[yyleng-2]=='\\'){
				output::errorUnclosedString();
                        	break;
			}  
			parsingStr=yytext;
			check=parse_string(parsingStr,result);
     			if(check!=-1){
   	   			parseIllegalSeq(parsingStr,check);
				output::errorUndefinedEscape(parsingStr.c_str());
				break;
			}
			output::printToken(yylineno,token,result.c_str());
			break;
		default:
			output::printToken(yylineno,token,yytext);
			break;
	 }
}
    return 0;
}
