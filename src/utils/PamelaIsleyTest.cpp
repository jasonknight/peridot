#include "Types.hpp"
#include "PamelaIsley.hpp"
namespace Utils = Peridot::Utils;
int main(void) {
   auto pam = new Peridot::PamelaIsley<Peridot::Token *>(); 
   auto eq = new Peridot::Token();
   Utils::InitializeToken(eq);
   eq->text = "=";
   
   auto one = new Peridot::Token();
   Utils::InitializeToken(one);
   one->text = "1";
   
   auto x = new Peridot::Token();
   Utils::InitializeToken(x);
   x->text = "x";
   
   auto y = new Peridot::Token();
   Utils::InitializeToken(y);
   y->text = "y";

   pam->InsertSimpleNode(eq,x,one)
       .InsertSimpleNode(eq,y,one)
       .Up();


   return 0;

}
