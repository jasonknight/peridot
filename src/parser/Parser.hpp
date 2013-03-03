#ifndef PERIDOT_PARSER_H
#define PERIDOT_PARSER_H

#include "utils/Types.hpp"
#include "utils/Utils.hpp"
#include <list>
namespace Peridot {
    namespace Parser {
        /**
         * The Parser is the gutty-wuts of the whole shebang.
         * Ideally, it takes a stream, lexer, tree, node, and token
         * implementation and lexes the stream into a token stack,
         * iterates over the tokens and creates the tree,
         * and then passes the tree on to an executor class that will
         * either execute it or compile it.
         * ideally, these should all be Pointers
         * */
        template<class LEXER, class TREE, class TOKEN>
        class Peter { // haha, get it, peter parser...I'm so funny
            public:
                Peter() {
                    // Until all of these are set, we can't do anything
                    tree_is_set     = false;
                    lexer_is_set    = false;
                }

                Peter& SetTree(TREE t) { tree_ = t; tree_is_set = true; return *this;}
                TREE GetTree() { return tree_; }

                Peter& SetLexer(LEXER l) {lexer_ = l; lexer_is_set = true; return *this;}
                LEXER GetLexer() { return lexer_;}


                Peter& SetCreateToken(std::function< TOKEN ()> func) {
                    CreateToken = func;

                    return *this;
                }

                Peter& Parse() {
                  TOKEN result = CreateToken();

                  delete result;
                  return *this;
                }

            private:
                bool        tree_is_set;
                bool        lexer_is_set;
                TREE        tree_;
                LEXER       lexer_;
                std::list<TOKEN> tokens_;
                std::function< TOKEN ()> CreateToken;
        };
    } // End Namespace Parser
} // End Namespace Peridot
#endif
