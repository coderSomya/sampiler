#ifndef __PARSER_H
#define __PARSER_H

#include <vector>
#include <iostream>
#include "./lexer.hpp"

enum NODE_TYPE{
  NODE_ROOT,
  NODE_VARIABLE,
  NODE_RETURN,
  NODE_PRINT,
  NODE_INT
};

struct AST_NODE{
    enum NODE_TYPE TYPE;
    std::string *VALUE;
    AST_NODE *CHILD;
    std::vector<AST_NODE *> SUB_STATEMENTS;
};

class Parser{
    public:
        Parser(std::vector<Token *> tokens){
            parserTokens=tokens;
            index=0;
            limit=tokens.size();
            current=parserTokens.at(index);
        }
        
        AST_NODE* parse(){
            AST_NODE *ROOT = new AST_NODE();
            ROOT->TYPE = NODE_ROOT;
            
            while(current->TYPE!=TOKEN_EOF){
                switch(current->TYPE){
                    case TOKEN_ID:{
                        ROOT->SUB_STATEMENTS.push_back(parseId());
                        break;
                    }    
                    case TOKEN_KEYWORD:{
                        ROOT->SUB_STATEMENTS.push_back(parseKeyword());
                        break;
                    }
                    default:{
                        std::cout<<"SYNTAX ERROR!"<<std::endl;
                        std::cout<<"current :"<<current->VALUE<<std::endl;
                        exit(1);
                    }
                }
                proceed(TOKEN_SEMICOLON);
            }
            
            return ROOT;
        }
    private:
        int limit;
        int index;
        Token* current;
        std::vector<Token *> parserTokens;
        
        Token* proceed(enum type TYPE){
            if(TYPE != current->TYPE){
                std::cout<<"SYNTAX ERROR!"<<std::endl;
                std::cout<<"expected: "<<TYPE<<" got: "<<current->TYPE<<std::endl;
                exit(1);
            }
            index++;
            if (index > limit) {
                std::cout<<"Parser ERROR!"<<std::endl;
                std::cout << "Unexpected end of input!" << std::endl;
                exit(1);
            }
            current = parserTokens.at(index);
            return current;
        }
        
        AST_NODE* parseInt(){
            if(current->TYPE!= TOKEN_INT){
                std::cout<<"SYNTAX ERROR!"<<std::endl;
                exit(1);
            }
            
            AST_NODE* newNode = new AST_NODE();
            newNode->TYPE = NODE_INT;
            newNode->VALUE = &current->VALUE;
            proceed(TOKEN_INT);
            
            return newNode;
        }
        
        AST_NODE* parseId(){
            std::string *buffer = &current->VALUE;
            proceed(TOKEN_ID);
            proceed(TOKEN_EQUALS);
            
            AST_NODE *newNode = new AST_NODE();
            newNode->TYPE = NODE_VARIABLE;
            newNode->CHILD = parseInt();
            newNode->VALUE = buffer;
            
            return newNode;
        }
        
        AST_NODE* parseReturn(){
            proceed(TOKEN_KEYWORD);
            AST_NODE * newNode = new AST_NODE();
            newNode->TYPE = NODE_RETURN;
            newNode->CHILD = parseInt();
            
            return newNode;
        }
        
        AST_NODE* parsePrint(){
            proceed(TOKEN_KEYWORD);
            AST_NODE * newNode = new AST_NODE();
            newNode->TYPE = NODE_PRINT;
            
            proceed(TOKEN_LEFT_PAREN);
            newNode->CHILD = parseInt();
            proceed(TOKEN_RIGHT_PAREN);
            
            return newNode;
        }
        
        AST_NODE* parseKeyword(){
            if(current->VALUE == "return"){
                return parseReturn();
            }
            else if(current->VALUE == "print"){
                return parsePrint();
            }
            else{
                std::cout<<"SYNTAX ERROR! UNDEFINED KEYWORD"<<std::endl;
                exit(1);
            }
        }
};
#endif