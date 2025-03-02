#ifndef __GENERATOR_H
#define __GENERATOR_H

#include "parser.hpp"
#include "fstream"
#include <sstream>

class Generator{
  public:
    Generator(AST_NODE* root, std::string filename){
        AST_ROOT=root;
        assemblyFile.open(filename + ".asm");
    }
    
    void writeSections(){
        assemblyFile << sectionData.str();
        assemblyFile << sectionText.str();
        
        assemblyFile.close();
    }
    
    void generate(){

        sectionData << "section .data\n\n";
        sectionText << "section .text\n\nglobal _start\n_start:";
        writeSections();
    }
  private:
    AST_NODE* AST_ROOT;
    std::ofstream assemblyFile;
    std::stringstream sectionData;
    std::stringstream sectionText;
};

#endif
