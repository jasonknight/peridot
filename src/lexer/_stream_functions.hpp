bool good() {
    return source_.good();
}
T& get(char &c) {
    source_.get(c);
    if (Utils::IsNewLine(c)) {
        line_number_++;
    } else if (Utils::IsFormattingWhitespace(c)) {
        white_space_seen_++; // this number should be attached to the token
    }
    return source_;
}
T& seekg(int pos) {
    source_.seekg(pos);
    return source_;
}
T& seekg(int off, std::ios_base::seekdir dir) {
    source_.seekg(off,dir);
    return source_;
}
int tellg() {
    return source_.tellg();
}
char peek() {
    return source_.peek();
}
T& unget() {
    source_.unget();
    return source_;
}

