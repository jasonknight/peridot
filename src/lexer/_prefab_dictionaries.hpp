InitializeDictionary<T>(dest);
#ifndef PERIDOT_WSTRING
dest->alphabet = "";
if (name == "StringSingleQuoted") {
    dest->name = "StringSingleQuoted";
    dest->begins_with = "'";
    dest->ends_with = "'";
    dest->terminator = '\'';
    dest->type = VSSTRING;
} else if (name == "StringDoubleQuoted") {
    dest->name = "StringDoubleQuoted";
    dest->begins_with = "\"";
    dest->ends_with = "\"";
    dest->terminator = '"';
    dest->type = VSTRING;
} else if (name == "Operators") {
    dest->name = "Operators";
    dest->alphabet = "&!+=-/*<>~|?%";
    dest->type = OPERATOR;
} else if (name == "Numbers") {
    dest->name = "Numbers";
    dest->alphabet = "+-1234567890ex.,";
    dest->begins_with = "+-1234567890";
    dest->type = NUMERICAL;
    dest->validator = [] (T& s,Token * t) -> bool {
        // i.e. don't allow 10. or 1.
        // useful for catching 10.times do etc
        if (t->end == '.') {
            s.unget();
            t->text = t->text.substr(0,t->text.size() - 1);
            t->end = *t->text.rbegin();
        }
        return true;
    };
} else if (name == "Parentheses") {
    dest->name = "Parens and Brackets";
    dest->alphabet = "()" + Lexer::D_PROG_BRACKETS;
    dest->match_times = 1;
    dest->type = BRACKET;
    dest->validator = [] (T& s,Token * result) -> bool {
        if (result->text == "(" || result->text == ")") {
            result->type = PAREN;
        } else if (result->text == "{" || result->text == "}") {
            result->type = BRACE;
        }
        return true;
    };
}
#else
dest->alphabet = L"";
if (name == L"StringSingleQuoted") {
    dest->name = L"StringSingleQuoted";
    dest->begins_with = L"'";
    dest->ends_with = L"'";
    dest->terminator = '\'';
    dest->type = VSSTRING;
} else if (name == L"StringDoubleQuoted") {
    dest->name = L"StringDoubleQuoted";
    dest->begins_with = L"\"";
    dest->ends_with = L"\"";
    dest->terminator = '"';
    dest->type = VSTRING;
} else if (name == L"Operators") {
    dest->name = L"Operators";
    dest->alphabet = L"&!+=-/*<>~|?%";
    dest->type = OPERATOR;
} else if (name == L"Numbers") {
    dest->name = L"Numbers";
    dest->alphabet = L"+-1234567890ex.,";
    dest->begins_with = L"+-1234567890";
    dest->type = NUMERICAL;
    dest->validator = [] (T& s,Token * t) -> bool {
        // i.e. don't allow 10. or 1.
        // useful for catching 10.times do etc
        if (t->end == '.') {
            s.unget();
            t->text = t->text.substr(0,t->text.size() - 1);
            t->end = *t->text.rbegin();
        }
        return true;
    };
} else if (name == L"Parentheses") {
    dest->name = L"Parens and Brackets";
    dest->alphabet = L"()" + Lexer::D_PROG_BRACKETS;
    dest->match_times = 1;
    dest->type = BRACKET;
    dest->validator = [] (T& s,Token * result) -> bool {
        if (result->text == L"(" || result->text == L")") {
            result->type = PAREN;
        } else if (result->text == L"{" || result->text == L"}") {
            result->type = BRACE;
        }
        return true;
    };
}
#endif
