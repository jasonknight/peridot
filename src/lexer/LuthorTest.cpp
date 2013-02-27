#include "Lexer.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "utils/Utils.hpp"
#include "utils/Types.hpp"
namespace Lexer = Peridot::Lexer;
namespace Utils = Peridot::Utils;

void PrintTokenInfo(Lexer::Token * result) {
    PeridotString name;
    Lexer::TokenTypeToName(result->type,name);
    std::cout << "Token: [" << result->text << "] of type [" << name << "] ";
    std::cout << " lineno [" << result->line_number << "] ";
    std::cout << "Terminated By: [" << result->terminated_by << "]" << std::endl; 
}
int main(void) {
    std::ifstream file;
    file.open("tests/numbers.txt");
    
    Lexer::TokenMonsterDictionary<std::ifstream> num; 
    Lexer::GetPreFabDictionary("Numbers",&num);

    auto * lex = new Lexer::Luthor<std::ifstream>(file,true);

    lex->AddDictionary(&num);
    
    auto result = new Lexer::Token;
    Lexer::InitializeToken(result); // Always call this
    std::ofstream outfile("tests/tokens.txt", std::ios::out);
    while(lex->Next(result)) {
        PrintTokenInfo(result);
        WriteToken(outfile,result); 
        InitializeToken(result);
    }
    outfile.close();
    delete lex;
    delete result;
    file.close();

    // Now let's read that file back in
    //
    std::cout << "Starting read in" << std::endl;
    std::ifstream tfile;
    tfile.open("tests/tokens.txt");

    auto * lex2 = new Lexer::Luthor<std::ifstream>(tfile,true);
    auto r = new Lexer::Token; 
    InitializeToken(r);

            
    Lexer::TokenMonsterDictionary<std::ifstream> t;
    t.alphabet = "Token";
    t.tigger = true;
    t.begins_with = "T";
    t.match_times = 6; 
    t.terminator = 'n';
    t.escape_character = Utils::ASCII::BACKSLASH; 
    lex2->AddDictionary(&t);

    

    t.validator = [] (std::ifstream & __s, Lexer::Token * __res) -> bool {
        if (__res->text == "Token") {
          auto tmp = new Lexer::Token; 
          Lexer::TokenMonsterDictionary<std::ifstream> n;
          n.name = "SubName";
          n.alphabet = "0123456789";
          n.tigger = true;
          n.type = Lexer::NUMERICAL;
          n.escape_character = Utils::ASCII::BACKSLASH;
          n.terminator = '\0';
          int value = 0;
          n.validator = Validator(std::ifstream,tmp_s,tmp_t) {
            value = atoi(tmp_t->text.c_str());
            return true;
          };
          __s.get(__res->start);
          __s.get(__res->end);
          __s.get(__res->terminated_by);
          if (!TokenMonster(n,__s,tmp)) {
            std::cout << "Failed to accquire start column" << std::endl;
            return false;
          }
          __res->start_column = value;
          __s.get(); // discard char
          if (!TokenMonster(n,__s,tmp)) {
            std::cout << "Failed to accquire line_number" << std::endl;
            return false;
          }
          __res->line_number = value;
          __s.get(); // discard char

          if (!TokenMonster(n,__s,tmp)) {
            std::cout << "Failed to accquire type" << std::endl;
            return false;
          }
          __res->type = (Lexer::TokenType)value;
          __s.get();
          if (!TokenMonster(n,__s,tmp)) {
            std::cout << "Failed to num chars" << std::endl;
            return false;
          }
          int numchars = value;
          char * buff = new char[numchars];
          __s.get();
          __s.read(buff,numchars);
          __res->text.assign(buff,numchars);
          delete tmp;
          return true; 
        }
        return false;
    };

    std::cout << "Starting loop to read in serialized tokens" << std::endl;
    while(lex2->Next(r)) {
        PrintTokenInfo(r);
        InitializeToken(r);
    }
    std::cout << "Loop finished" << std::endl;
    
    delete lex2;
    delete r;
    return 0;
}
