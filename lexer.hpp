#ifndef __LEXER_H
#define __LEXER_H

#include <sstream>
#include <string>
#include <vector>
#include <iostream>

enum type{
    TOKEN_ID,
    TOKEN_INT,
    TOKEN_EQUALS,
    TOKEN_SEMICOLON,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_KEYWORD,
    TOKEN_EOF,
    TOKEN_STRING,
    TOKEN_QUOTES
};

class Token{
    
    public:
        enum type TYPE;
        std::string VALUE;
};


class Lexer{
    public:
        Lexer(std::string sourceCode){
            source=sourceCode;
            cursor=0;
            size=sourceCode.length();
            current=sourceCode.at(cursor);
            lineNumber=1;
            characterNumber=0;
        }
        
        
        std::vector<Token *> tokenize(){
            std::vector<Token *> tokens;
            Token *token;
            bool notEof = true;
            
            while(cursor<size && notEof){
                checkAndSkip();
                if(isalpha(current) || current == '_'){ // logic for ids
                    //we allow ids to start with alphabets or '_' character
                    
                    tokens.push_back(tokenizeId());
                    continue;
                }
                if(isdigit(current)) { //logic for integer literals
                    tokens.push_back(tokenizeInt());
                    continue;
                }
                
                switch(current){
                    case '=':{
                        tokens.push_back(tokenizeSpecial(TOKEN_EQUALS));
                        break;
                    }
                    case '(':{
                        tokens.push_back(tokenizeSpecial(TOKEN_LEFT_PAREN));                        
                        break;
                    }
                    case ')':{
                        tokens.push_back(tokenizeSpecial(TOKEN_RIGHT_PAREN));
                        break;
                    }
                    case ';':{
                        tokens.push_back(tokenizeSpecial(TOKEN_SEMICOLON));
                        break;
                    }
                    //print("hello world");
                    case '"':{
                        tokens.push_back(tokenizeSpecial(TOKEN_QUOTES));
                        tokens.push_back(tokenizeString());
                        tokens.push_back(tokenizeSpecial(TOKEN_QUOTES));
                        break;
                    }
                    default:{
                        std::cout<<"Lexer error, undefined symbol"<<std::endl;
                        std::cout<<"at "<<lineNumber<<":"<<characterNumber<<std::endl;
                        exit(1);
                    }
                }
                
            }
            
            return tokens;
        }
        
    private:
        std::string source;
        int cursor;
        int size;
        char current;
        int lineNumber;
        int characterNumber;
        
        char advance(){
            if(cursor<size){
                char temp = current;
                cursor++;
                characterNumber++;
                current = (cursor < size) ? source.at(cursor) : '\0';
                return temp;
            }
            else{
                return '\0';
            }
        }
        
        char peek(int offset = 0){
            if(cursor + offset < size){
                return source.at(cursor+offset);
            }
            else{
                return '\0';
            }
        }
        
        void checkAndSkip(){
            while(current ==' '|| current == '\n' || current == '\t' || current == '\r'){
                if(current=='\n') {
                    lineNumber++;
                    characterNumber=0;
                }
                advance();
            }
        }
        
        Token* tokenizeId(){
            std::stringstream buffer;
            buffer << advance();
            
            while(isalnum(current) || current == '_'){
                buffer<<advance();
            }
            
            Token* newToken = new Token();
            
            newToken->TYPE=TOKEN_ID;
            newToken->VALUE=buffer.str();
            
            return newToken;
        }
        
        Token* tokenizeInt(){
            std::stringstream buffer;
            buffer << advance();
            
            while(isdigit(current)){
                buffer<<advance();
            }
            
            Token* newToken = new Token();
            
            newToken->TYPE=TOKEN_INT;
            newToken->VALUE=buffer.str();
            
            return newToken;
        }  
        
        Token* tokenizeSpecial(enum type Type){
            std::stringstream buffer;
            
            Token* newToken = new Token();
            
            newToken->TYPE=Type;
            newToken->VALUE=std::string(1,advance());
            
            return newToken;
        }
        
        Token* tokenizeString(){
            std::stringstream buffer;
            while(current!='"'){
                if(current=='\0'){
                    std::cout<<"Lexer error: Missing quotes"<<std::endl;
                    exit(1);
                }
                buffer<<advance();
            }
            Token* newToken = new Token();
            
            newToken->TYPE=TOKEN_STRING;
            newToken->VALUE=buffer.str();
            
            return newToken;
        }
};

#endif