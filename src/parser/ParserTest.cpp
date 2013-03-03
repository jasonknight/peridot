#include "utils/Types.hpp"
#include "lexer/Lexer.hpp"
#include "utils/Utils.hpp"
#include "utils/PamelaIsley.hpp"
#include "parser/Parser.hpp"
#include <sstream>
namespace Lexer     = Peridot::Lexer;
namespace Utils     = Peridot::Utils;
namespace Parser    = Peridot::Parser;
int main(void) {
   std::stringstream source;
   source.str("1 + 1");

   auto Pamela  = new Peridot::PamelaIsley<Peridot::Token *>();
   auto Lex     = new Lexer::Luthor<std::stringstream>(source,true);
   auto numbers = new Lexer::TokenMonsterDictionary<std::stringstream>();
   Lexer::GetPreFabDictionary("Numbers",numbers);
   Lex->AddDictionary(numbers);

   // The Parser
   auto Peter   = new Parser::Peter<Lexer::Luthor<std::stringstream> *,
                                    Peridot::PamelaIsley<Peridot::Token *>*, 
                                    Peridot::Token *>();
   Peter->SetCreateToken([] () -> Peridot::Token* {
          auto token = new Peridot::Token;
          Utils::InitializeToken(token);
          return token;
   });

   Peter->Parse();
}
