#ifndef PERIDOT_WSTRING
const PeridotString D_ALPHA = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
const PeridotString D_ALPHA_LOWER = "abcdefghijklmnopqrstuvwxyz";
const PeridotString D_ALPHA_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const PeridotString D_NUMERIC = "1234567890";
const PeridotString D_NUMERIC_EXT = "+-,.1234567890ex";
const PeridotString D_ALPHA_NUMERIC = D_ALPHA + D_NUMERIC;
const PeridotString D_OPERATORS = "!/*%+-^&><=~|";
const PeridotString D_PUNCTUATION = "!.,;:?";
const PeridotString D_VARIABLES = "@$";
const PeridotString D_ALL_BRACKETS = "()[]{}<>";
const PeridotString D_PROG_BRACKETS = "[]{}";
const PeridotString D_PARENS = "()";
const PeridotString D_QUOTES = "\"'";
const PeridotString D_WHITESPACE = "\t \r\n";

// Prefab Special Dictionaries that are customizeable
const PeridotString CLASS_CONSTANTS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const PeridotString WHITESPACE = " \n\r\t";
#else
const PeridotString D_ALPHA = L"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
const PeridotString D_ALPHA_LOWER = L"abcdefghijklmnopqrstuvwxyz";
const PeridotString D_ALPHA_UPPER = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const PeridotString D_NUMERIC = L"1234567890";
const PeridotString D_NUMERIC_EXT = L"+-,.1234567890ex";
const PeridotString D_ALPHA_NUMERIC = D_ALPHA + D_NUMERIC;
const PeridotString D_OPERATORS = L"!/*%+-^&><=~|";
const PeridotString D_PUNCTUATION = L"!.,;:?";
const PeridotString D_VARIABLES = L"@$";
const PeridotString D_ALL_BRACKETS = L"()[]{}<>";
const PeridotString D_PROG_BRACKETS = L"[]{}";
const PeridotString D_PARENS = L"()";
const PeridotString D_QUOTES = L"\"'";
const PeridotString D_WHITESPACE = L"\t \r\n";

// Prefab Special Dictionaries that are customizeable
const PeridotString CLASS_CONSTANTS = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const PeridotString WHITESPACE = L" \n\r\t";

#endif

