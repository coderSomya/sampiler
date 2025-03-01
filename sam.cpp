#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "./lexer.hpp"

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
    
    for(auto x: tokens){
        std::cout<<x->TYPE<<" : "<<x->VALUE<<std::endl;
    }
    std::cout<<"end of the program"<<std::endl;
    return 0;
}