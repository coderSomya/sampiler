#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"
#include "generator.hpp"

int main(int argc, char ** argv){
    
    if(argc < 2){
        std::cout<<"Please supply the source file";
        exit(1);
    }
    std::cout<<"Reading from file: "<<argv[1]<<std::endl;
    std::ifstream sourceFileStream(argv[1]);
    
    std::stringstream buffer;
    char temp;
    
    while(sourceFileStream.get(temp)){
        buffer << temp;
    }
    
    std::string sourceCode = buffer.str();
    std::cout<<"code: \n"<<sourceCode<<std::endl;
    
    Lexer lexer(sourceCode);
    
    std::vector<Token *> tokens = lexer.tokenize();
    
    if (tokens.back()->TYPE != TOKEN_EOF){
        Token * EOFNode = new Token();
        EOFNode->TYPE = TOKEN_EOF;
        tokens.push_back(EOFNode);
    }

    for(auto x: tokens){
        std::cout<<x->TYPE<<" : "<<x->VALUE<<std::endl;
    }
    
    // Parser parser(tokens);
    // AST_NODE* root = parser.parse();
    
    // std::cout<<"parsed! number of statements = "<<root->SUB_STATEMENTS.size()<<std::endl;
    
    Generator generator(NULL,argv[1]);
    generator.generate();
    
    std::cout<<"end of the program"<<std::endl;
    return 0;
}