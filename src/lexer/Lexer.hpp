#ifndef PERIDOT_LEXER_H
#define PERIDOT_LEXER_H
/**
 * Copyright (c) 2013 Red(E) Tools LTD, Jason Martin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * -------------------------------------------------------------------------------------------------------
 *
 * Three couples independently decided to join a local church, the first was retired, the second
 * middle aged, and the third was newlywed.
 *
 * The first couple went to the church's minister and asked to join, he responded: "Our church practices
 * abstinence from all sexual behavior, before you can join, you must prove that you can abstain for the 
 * next two weeks."
 *
 * The second couple and the third couple were given the same challenge. Don't have any sex for two weeks.
 * 
 * So the first couple returns after two weeks and reports to the minister that they had no problem
 * abstaining from sex, so they were welcome to join the church.
 *
 * The second couple returns after two weeks and reports to the minister that they had a lot of trouble
 * abstaining from sex, but they managed, so they were welcome to join the church.
 *
 * The third couple returns after two weeks and reports to the minister: "Well, everything was going fine
 * until SHE dropped a can of paint."
 *
 * "A can of PAINT?!" exclaims the minister.
 *
 * "Yeah," says the husband, "She dropped the can and when she bent over to pick it up, lust just took
 * over, and I had to take her right there and then!"
 *
 * The minister just shook his head and said: "I am sorry, but someone with such low impulse control is just
 * not welcome in our church."
 *
 * "That's okay." says the man, "We're not welcome in Home Depot either."
 *
 * */
#include <functional>
#include <string>
#include <iostream>
#include <cassert>
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include "utils/Utils.hpp"
#include "utils/Types.hpp"
#include "Lexer.hpp"
namespace Peridot {
namespace Lexer {
    
    /**
     * See the .rb file create_token_exception_to_message.rb*/
    enum TokenExceptionType {
        UNRECOGNIZED_ENTITY,
        BAD_STREAM
    };
    /* Pre-Made Dictionaries */
    #include "_dictionaries.hpp" 
    
    /**
     * Not sure what to do with these...it's actually faster without
     * caching if you write your tiggertons cleverly...
     * */
    inline bool Cached(const std::bitset<48> b, const PeridotChar c) {
        if (c > 126 || c < 33) { return false;}
        if (c % 2 != 0) { return false;}
        return b[(c - 33) - ((c - 33) / 2 )];
    }
    inline void CacheSet(std::bitset<48> &b, const PeridotChar c) {
        if (c > 126 || c < 33) { return;}
        if (c % 2 != 0) { return;}
        b[(c - 33) - ((c - 33) / 2 )] = 1;
    }
    inline void TokenExceptionToMessage(TokenExceptionType t, PeridotString& message) {
        switch(t) {
           #include "_token_exception_to_msg.hpp"
        }
    }
    /**
     * TokenMonsterDictionary is a struct that contains a list of accepted characters for this
     * class, as well as some members that define simple rules, like what should be the first
     * character, the last character, or can it begin with a limited set of characters. For instance
     * a Numerical Token can be +5.23 or -9.123456e-13 or 0x4323. So it's dictionary would be
     * {+-123456789.,ex} but ex1234 is not a valid number, so we need to say that the first char
     * must be 1234567890 or - or + etc. */
    template <typename T>
    struct TokenMonsterDictionary {
        /*
         * Tiggers vs. Eeyores:
         * Tiggers look for inclusion, so the alphabet you pass in
         * will be checked to see if the current_character is included in
         * the string, if it is, then continue, otherwise, goto rejected.
         *
         * Eeyores by contrast do the opposite, if the current_character is
         * in the string, then it will goto rejected, otherwise, if it is not present,
         * then it will continue. This makes it easier when you have a large number
         * of acceptable inputs, but a smaller number of unacceptable inputs, this
         * way, you can search and categorize much faster.
         *
         * As an example: Variables in Ruby: @|@@|$[\w]+ would need an alphabet like so:
         * @$aAbBcCdDeEfFgG... and so on, that's over 54 items that will need to be searched.
         * and that doesn't even take into account extended alphabets, which should be possible.
         *
         * This is also the case if you want to parse a text file, say of french phrases and categorize
         * them. This parser is completely general, so it's better to just say what a variable cannot 
         * include.
         *
         * The one exception to an Eeyore is this: begins_with is not respected, meaning begins_with
         * is always a tigger. The same is true for ends_with.
         *
         * You can implement contrary begins_with and ends_with with a validator that provides the
         * ability to validate what the parser thinks based on some exceptional situations.
         * */
        bool                       tigger;
        PeridotChar                escape_character;
        PeridotChar                terminator; // sometimes we want to accept everything but a single char
                                        // however, that PeridotChar is also a part of the set for detection
                                        // this is the case with quoted strings, they start with " and
                                        // then anything else is okay except ".
                                        // This would allow us to accept a string with a simple blank
                                        // alphabet, with a starts_with of " and a terminator of " and
                                        // an escape PeridotChar of \. 
        int                   match_times;
        TokenType             type;
        PeridotString         name;
        PeridotString         alphabet;
        PeridotString         begins_with;
        PeridotString         ends_with;
        //std::bitset<48>     cache;
        /*
         * validator requires a function, probably a lambda. See the LexerTest.cpp RunTest2 function
         * for an example of using a validator.
         * In this case, you can also have access to the stream used to find the token.*/
        std::function<bool (T&, Token* )> validator; // order is always const, input, output
    };
    
    template <class T>
    void InitializeDictionary(TokenMonsterDictionary<T> *dict) {
        Utils::Nil(dict,"InitializeDictionary(dict)");
        dict->tigger = true;
        dict->name = "";
        dict->type = UNKNOWN;
        dict->alphabet = "";
        dict->begins_with = "";
        dict->ends_with = "";
        dict->escape_character = '\0';
        dict->terminator = '\0';
        dict->match_times = -1;
    }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstring-compare"
    /**
     * Here we provide some default starter dictionaries that you can later customize,
     * name must be a "" string, or an PeridotString
     * */
    template <class T,class S>
    void GetPreFabDictionary(const S &name, TokenMonsterDictionary<T> *dest) {
        Utils::Nil(dest,"GetPreFabDictionary(dest)");
        dest->tigger = true; 
        dest->escape_character = Utils::ASCII::BACKSLASH;
        #include "_prefab_dictionaries.hpp"        
        
    }
#pragma clang diagnostic pop
    /**
     * A TokenMonster just wants to get a token, anything is a token, we aren't really concerned with
     * complex differentiation at this point. The parser should handle the semantics of a token and
     * whether or not it violates some high level rule.
     * */
    template <class T>
    bool TokenMonster (TokenMonsterDictionary<T>& dictionary, T& input_stream, Peridot::Token *result) {
        Utils::Nil(result,"TokenMonster(result)");
#ifdef LEXER_DEBUG
        std::cout << std::endl << "##Beginning TokenMonster with: " << dictionary.name << std::endl;
#endif
        int start_position = input_stream.tellg(); // so we can restore position when we fail
        int num_matches_found = 0;
        PeridotChar current_character;
        PeridotString buffer;
        bool just_started = true;
        unsigned found;
        while(input_stream.good() && !input_stream.eof()) {
            input_stream.get(current_character);
#ifdef LEXER_DEBUG
            std::cout << std::endl << "##Running loop: [" << current_character << "]" << std::endl;
#endif
            if (input_stream.eof()) {
                /* 
                 * OMFG BBQ TURNIP! Is that a goto statement I see. Yes Bitch it is,
                 * and if you say one fucking word about how it could all be done with
                 * a loop you will be shot. Out of a Cannon. Into the sun...
                 * */
#ifdef LEXER_DEBUG
                std::cout << std::endl << "EOF reached" << std::endl;
#endif
                goto check_buffer;
            }
#ifdef LEXER_DEBUG
            std::cout << "## Excape Sequence Check $current_character: [" << current_character << "] == [" << dictionary.escape_character << "]" << std::endl;
#endif
            if (current_character == dictionary.escape_character) { // escape character
                // we get the next character
                input_stream.get(current_character);
#ifdef LEXER_DEBUG
                std::cout << std::endl << "Escape Character seen, next PeridotChar is: " << current_character << std::endl;
#endif
                buffer += current_character;
                continue;
            }
            if (just_started == false && current_character == dictionary.terminator && dictionary.terminator != '\0') {
                buffer += current_character;
                result->end = current_character;
#ifdef LEXER_DEBUG
                std::cout << std::endl << "Terminator seen, " << current_character << " " << buffer << std::endl;
#endif
                input_stream.get(current_character); // advance
                current_character = result->end; // restore the current char
                                                 // when we see the terminator, we also includ it in the string
                                                 // so we need to advance one more because we restore the pointer
                                                 // in the stream to current_PeridotChar -1
                                                 // but with complex dictionaries, like with a string matcher,
                                                 // this will reset the pointer to the last " seen, so we need to
                                                 // advance +1 so that the next restored position is " + 1
                goto check_buffer;
            }
            if (just_started) {
                if (dictionary.begins_with.length() > 0) {
                    // Notice that this is always a tigger, regardless of
                    // the dictionary.tigger var.
                    found = dictionary.begins_with.find(current_character);
                    if (found > dictionary.begins_with.size()) {
#ifdef LEXER_DEBUG
                        std::cout << std::endl << "rejecting because of begins_with" << dictionary.begins_with << " " << current_character << std::endl;
#endif
                        goto rejected;
                    } else {
                        num_matches_found++;
                        just_started = false;
                    }
                } else {
                    goto find_char;
                }
            } else {
                find_char:
                if (dictionary.alphabet.length() == 0) {
#ifdef LEXER_DEBUG
                    std::cout << "Dictionary length is zero, setting to 99" << std::endl;
#endif
                    found = 99; // i.e. blank dictionary is the ultimate Eeyoreton. 
                                // Notice that later, it uses the tigger flag, even
                                // though it's an eeyoreton, the tigger flag MUST be
                                // set to true ideally this could be rewritten to work
                                // the normal way, but this is probably a bit faster
                    num_matches_found++;
                } else {
                    found = dictionary.alphabet.find(current_character);
                }
            }
            // For some reason, in the latest clang, we cannot use std::string::npos.
            // found will be a huge unsigned int, like 4294967295 when the string
            // isn't found. This is new, because when I compiled the latest trunk
            // 1 week ago it was possible, now it's not...hope this doesn't change
            // again
#ifdef LEXER_DEBUG
            std::cout << found << " > " << dictionary.alphabet.size() << std::endl;
#endif 
            if ((found < dictionary.alphabet.size()) == dictionary.tigger) {
                num_matches_found++;
                if (just_started) {
                    result->start = current_character;
                    just_started = false;
                }
                append_and_continue:
                buffer += current_character;
                result->end = current_character;
            } else {
#ifdef LEXER_DEBUG
               std::cout << "found does not match " << std::endl;
#endif 
               result->terminated_by = current_character;
               goto check_buffer; 
            }
            // So we can limit the number of matches
#ifdef LEXER_DEBUG
            std::cout << "Match Times" << dictionary.match_times << " " << num_matches_found << std::endl;
#endif
            if (dictionary.match_times && dictionary.match_times == num_matches_found) {
                input_stream.get(current_character); // advance
                current_character = result->end; 
                goto check_buffer;
            }
        }
        /*
         * We check the buffer to see if anything matched and was inserted
         * before the failure was encountered.
         * */
        check_buffer:
            if (buffer.length() > 0) {
               // Here we can verify that the last character is
               // in some set of predefined characters, it's a simple
               // tiggerton, so if you need more specific behavior
               // you'll have to use a validator
               if (dictionary.ends_with.length() > 0) {
                 found = dictionary.ends_with.find(current_character);
                 if (found > dictionary.ends_with.size()) {
                    goto accepted;
                 } else {
#ifdef LEXER_DEBUG
                    std::cout << "Rejecting due to ends_with in check_buffer" <<  dictionary.ends_with << std::endl;
#endif
                    goto rejected;
                 }
               } // end of ends_with code
               goto accepted; 
            } else {
                goto rejected;
            }
        accepted:
            result->text = buffer;
            result->type = dictionary.type;
            result->start_column = start_position;
            // a validator is where you can do advanced matching and or parsing.
            // in fact, you could do almost anything. remember you MUST return true
            // here or it will fail. Usually that's not actually what you want,
            // and a validator is more of a refiner. 

            input_stream.seekg(((int)input_stream.tellg()) - 1); // backup one character, generally this will be a 
                                                                 // whitespace char, or semi-colon or some such.

            if (dictionary.validator) {
                // REMEMBER! Validators are responsible for tracking and restoring
                // the position of the stream!
                if (dictionary.validator(input_stream,result) == false) {
                    goto rejected;
                }
            }
                        return true;
        rejected:
            input_stream.seekg(start_position); // i.e. restore the position in the stream for another tigger to look at.
            return false;
    } // End bool TokenMonster  
    /**
     * The Luthor class (get it Lexer::Luthor...i'm so funny) is the main
     * Peridot Lexer that accepts a stream and then parses it, maintaining a 
     * token chain from the root on down.
     * */
    template <class T>
    class Luthor {
        public:
            Luthor(T& s, bool ignorews = false) : source_(s) {
                ignore_whitespace_ = ignorews;
                line_number_ = 1;
                white_space_seen_ = 0;
                if (ignore_whitespace_) {
                    ignore_these_chars_ = D_WHITESPACE; // see _dictionaries.hpp
                }
            }
            /**
             * All methods present a fluid interface unless that
             * isn't possible. If you need to return a variable, the
             * output should be one of the arguments except in the case
             * of getters, which are supposed to return a reference.
             * */
            inline Luthor& SetIgnoreTheseChars(const PeridotString& s) {
                ignore_these_chars_ = s;
                return *this;
            }
            inline std::string& GetIgnorTheseChars() {
                return ignore_these_chars_;
            }
            inline int GetWhiteSpaceSeen() {
                return white_space_seen_;
            }
            inline Luthor& AddDictionary(TokenMonsterDictionary<T> *d) {
                Utils::Nil(d,"Luthor->AddDictionary");
                dictionaries_.push_back(d);
                return *this;
            }
            inline Luthor& ConsumeWhitespace() {
                PeridotChar c;
                white_space_seen_ = 0;
                source_.get(c); // preload the char
                bool inloop = false;
                while (source_.good() && (ignore_these_chars_.find(c) != PeridotString::npos) ) {
#ifdef LEXER_DEBUG
                    std::cout << "Char : " << c << " consumed" << std::endl;
#endif
                    // Generally we make a distinction between nls and tabs/spaces
                    // this way we can resolve blocks based on their preceding white
                    // space in a pinch as a last ditch effort to figure out
                    // what the programmer meant.
                    if (Utils::IsNewLine(c)) {
                        line_number_++;
                    } else if (Utils::IsFormattingWhitespace(c)) {
                        white_space_seen_++; // this number should be attached to the token
                    }
                    source_.get(c);
                }
                if (inloop == false) {
                    source_.unget(); // backup if we never consumed space
                }
#ifdef LEXER_DEBUG
                std::cout << "Whitespace consumed" << std::endl;
#endif
                return *this;
            }
            bool Next(Peridot::Token * result) {
                Utils::Nil(result,"Luthor::Next(result)");
                ConsumeWhitespace();
                if (source_.good()) {
                    bool found = false;
                    for (dit_ = dictionaries_.begin(); ( ( dit_ != dictionaries_.end() ) && (found == false) ); ++dit_) {
                        auto dictionary = *dit_;
#ifdef LEXER_DEBUG
                        std::cout << "dit is: " << dictionary->alphabet << std::endl;
#endif
                        found = TokenMonster(*dictionary,source_,result); 
                    }  
                    if (result->line_number == 0) {
                        result->line_number = line_number_;
                    }
#ifdef LEXER_DEBUG
                    std::cout << "Returning : " << found << std::endl;
#endif
                    return found;
                }
#ifdef LEXER_DEBUG
                std::cout << "Never found anything" << std::endl;
#endif
                return false;
            }

            // Stream interface functions provided by a partial
            #include "_stream_functions.hpp"    
        private:
            T& source_;
            /* Whether or not we ignore white space */
            bool ignore_whitespace_;
            /* Accumulator for the line numbers */
            int line_number_;
            int white_space_seen_;
            /* Otherwise we need to know what chars to ignore*/
            PeridotString ignore_these_chars_;
            typename std::vector<Lexer::TokenMonsterDictionary<T>*>::iterator dit_;
            std::vector<TokenMonsterDictionary<T>*> dictionaries_;
    };
 
      } // End Lexer Namespace
} // End Peridot Namespace
#endif
