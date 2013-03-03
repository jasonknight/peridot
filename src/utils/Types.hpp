#ifndef PERIDOT_TYPES_H
#define PERIDOT_TYPES_H
#include <typeinfo>
#include <functional>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
typedef std::string PeridotString;
typedef char      PeridotChar;
//#define PERIDOT_WSTRING
#define Validator(x,y,z) [&] (x& y, Peridot::Token * z) -> bool

namespace Peridot {
    /**
     * A TokenType is a primitive, like Numerical, Word, Punctuation, Operator, Symbol,
     * and different types of Brackets and Parentheses. */
    enum TokenType {
        UNKNOWN,
        NUMERICAL,
        WORD, // Here we have general lexical unit types for parsing natural language.
        VERB,
        ADVERB,
        PREPOSITION,
        CONJUNCTION,
        NOUN,
        ADJECTIVE,
        PARTICLE,
        ARTICLE,
        PRONOUN,
        QUOTE,
        SQUOTE,
        PUNCTUATION,
        OPERATOR,
        PAREN,
        BRACKET,
        BRACE,
        KEYWORD, /* After this point, we have more specialized types, like KMODULE. K for Keyword*/
        KVARDECL,
        KFALSE,
        KTRUE,
        KNIL,
        KNULL,
        KCLASS,
        KMODULE,
        KFOR,
        KWHILE,
        KUNTIL,
        KIF,
        KTHEN,
        KELIF,
        KELSE,
        KEND,
        KDEFINE,
        KALIAS,
        KBEGIN,
        KDO,
        KENSURE,
        KTHROW,
        KCATCH,
        KRESCUE,
        KRETRY,
        KREDO,
        KTHIS,
        KSUPER,
        KUNLESS,
        KWHEN,
        KWITH,
        KSWITCH,
        KCASE,
        KBREAK,
        KNEXT,
        KCONTINUE,
        KYIELD,
        KAND,
        KOR,
        KNOT,
        KIN,
        KEXPONENT, //like 2**2
        KRETURN,
        KMETHOD, // Different from function if we actually make a distinction
        KFUNCTION, 
        KLAMBDA,
        KNUMERIC, // Begin type keywords
        KSHORT,
        KINT,
        KLONG,
        KBOOL,
        KFLOAT,
        KDOUBLE,
        KSTRING,
        KCHAR,
        KWSTRING,                                    
        VINSTANCE, // V means Variable, i.e. user space variable.
        VGLOBAL,
        VCLASS,
        VSYM,
        VFUNCTION,
        VNUMERIC,
        VSHORT,
        VINT,
        VLONG,
        VBOOL,
        VFLOAT,
        VDOUBLE,
        VSTRING,
        VSSTRING, // Single Quoted String
        VCHAR,
        VWSTRING,
        VHASH,
        VARRAY,
        VOBJECT,
        VLAMBDA // if we want to make a distinction
    };
     /**
     * Tokens are represented as a chain with previous and next pointing to their siblings
     * so that it should be possible to navigate forward and backward in the chain.
     * We want to populate the struct with relevant pieces of information so that the
     * parser can ultimately decide what it means in context.
     * */
    struct Token {
      PeridotChar                          start;
      PeridotChar                          end;
      PeridotChar                          terminated_by; // This will often be a ASCII::SP or perhaps a ;
                                                   // that can help us predict what to do. It may be
                                                   // a . so that we know that this is probably an
                                                   // object and the next WORD will be a symbol that
                                                   // needs to be sent to the object
      int                                  start_column;
      int                                  line_number;
      TokenType                            type;
      PeridotString                        text;
    };
    /*
     * Represents a single node
     * */
    template <class T>
    class Node { 
        public:
        // Links to other Node's
        Node<T> * left_; // node containing the left side
        Node<T> * right_; // node containing the right side
        Node<T> * parent_; // the parent
        Node<T> * down_; // down node
        // the contents
        T contents_;
        /**
         * This is the "default" constructor making this "node" a
         * sentinel so that we can detect the end of the branch.
         * */
        Node()  { // creates the "sentinel"
            contents_ = NULL;
            left_       = this;
            right_      = this;
            parent_     = this;
            down_       = this;
        }
        Node<T>& SetContents(T c) { contents_ = c; return *this;}
        Node<T>& SetLeft(Node<T> * n) { left_ = n; return *this;}
        Node<T>& SetRight(Node<T> * n) { right_ = n; return *this;}
        Node<T>& SetParent(Node<T> * n) { parent_ = n; return *this;}
        Node<T>& SetDown(Node<T> * n) { down_ = n; return *this;}
        Node<T> * GetLeft() { return left_;}
        Node<T> * GetRight() { return right_;}
        Node<T> * GetParent() { return parent_;}
        Node<T> * GetDown() { return down_;}
        T GetContents() { return contents_;}
        std::string& ToString() { return contents_->text;}
        const char * ToCString() {return contents_->text.c_str();}
        int ToInt() { return atoi(contents_->text.c_str()); }
       }; // End Struct Node     
} // End Namespace Peridot
#endif
