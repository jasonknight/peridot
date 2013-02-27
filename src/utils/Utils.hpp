#ifndef PERIDOT_UTILS_H
#define PERIDOT_UTILS_H
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
 * Harry, Bill, and Carl are sitting at the corner bar one evening, when their friend Ted comes in
 * looking very distressed.
 * 
 * "Ted! you look awful," says Harry, "What's wrong?"
 *
 * "Last night I got really drunk and I think I was abducted."
 *
 * Everyone is shocked, and Bill asks, "Well, what did they do
 * to you?"
 *
 * "All I remember is being anally probed." says Ted.
 *
 * Everyone is horrified. "I heard they do that." 
 *
 * Bill, obviously interested in Alien phenomenon asks: 
 * "Well, what did the alien look like?"
 *
 * Ted responds: "Carl."
 */
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <assert.h>
namespace Peridot {
  namespace Utils {
    namespace ASCII {
        /**
         * Table of ASCII Non Printing codes,
         * for general use, mainly be the Lexer
         * */
        const char 	 NUL		=		0x00;
        const char 	 SOH		=		0x01;
        const char 	 STX		=		0x02;
        const char 	 ETX		=		0x03;
        const char 	 EOT		=		0x04;
        const char 	 ENQ		=		0x05;
        const char 	 ACK		=		0x06;
        const char 	 BEL		=		0x07;
        const char 	 BS		    =		0x08;
        const char 	 HT		    =		0x09;
        const char 	 LF		    =		0x0A;
        const char 	 VT		    =		0x0B;
        const char 	 FF		    =		0x0C;
        const char 	 CR		    =		0x0D;
        const char 	 SO		    =		0x0E;
        const char 	 SI		    =		0x0F;
        const char 	 DLE		=		0x10;
        const char 	 DC1		=		0x11;
        const char 	 DC2		=		0x12;
        const char 	 DC3		=		0x13;
        const char 	 DC4		=		0x14;
        const char 	 NAK		=		0x15;
        const char 	 SYM		=		0x16;
        const char 	 ETB		=		0x17;
        const char 	 CAN		=		0x18;
        const char 	 EM		    =		0x19;
        const char 	 SUB		=		0x1A;
        const char 	 ESC		=		0x1B;
        const char 	 FS		    =		0x1C;
        const char 	 GS		    =		0x1D;
        const char 	 RS		    =		0x1E;
        const char 	 US		    =		0x1F;
        const char 	 SP		    =		0x20;
        const char   BACKSLASH  =       0x5C;
        const char 	 DEL		=		0x7F;        
    } // End Namespace ASCII
    inline bool IsWhitespaceCharacter(const char c) {
        namespace ascii = Peridot::Utils::ASCII;
        return ( 
                 c == ascii::HT || 
                 c == ascii::LF ||
                 c == ascii::CR ||
                 c == ascii::FF ||
                 c == ascii::SP
               );
    }
    inline bool IsNewLine(const char c) {
        namespace ascii = Peridot::Utils::ASCII;
        return (
                    c == ascii::CR ||
                    c == ascii::FF ||
                    c == ascii::LF
                );
    } 
    inline bool IsFormattingWhitespace(const char c) {
        namespace ascii = Peridot::Utils::ASCII;
        return (
                    c == ascii::HT ||
                    c == ascii::SP 
                );
    }
    inline void IntToString(const int i, std::string& dest) {
        std::stringstream ss;
        ss << i;
        dest.assign(ss.str());
    }
    
    void ExceptionToMessage(int ex, std::string & msg) {
        switch(ex) {
            case 666:
                msg = "You have a null pointer being passed to a Peridot method. All Peridot methods that accept pointers \
                       call Nil(pointer) which throws this error.";
                break;
            default:
                msg = "I don't know what the fuck happened, but it's bad.";
                break;
        }
    }
    void Puts(std::string & s) {
        std::cout << s << std::endl;
    }
    void Nil(void * p) {
        if (p == NULL) {
            // We can't seem to throw errors...weird..
            std::string e;
            ExceptionToMessage(666,e);
            Puts(e);
            assert(false);
        }
    }
  } // End Namespace Utils
}// End Namespace Peridot
#endif
