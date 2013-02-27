#ifndef PERIDOT_TYPES_H
#define PERIDOT_TYPES_H
#include <typeinfo>
typedef std::string PeridotString;
typedef char      PeridotChar;
//#define PERIDOT_WSTRING
#define Validator(x,y,z) [&] (x& y, Peridot::Lexer::Token * z) -> bool
#endif
