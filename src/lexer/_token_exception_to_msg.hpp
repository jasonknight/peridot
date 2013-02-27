
#ifndef PERIDOT_WSTRING
case TokenExceptionType::UNRECOGNIZED_ENTITY:
	message = "The Lexer encountered an unrecognized entity '%s' at line %d column %d. This is most likely caused by a set of TokenTypeDictionary's that are too restrictive considering the input. It may also simply be an erroneus char value.";
	break;

#else
case TokenExceptionType::UNRECOGNIZED_ENTITY:
	message = L"The Lexer encountered an unrecognized entity '%s' at line %d column %d. This is most likely caused by a set of TokenTypeDictionary's that are too restrictive considering the input. It may also simply be an erroneus char value.";
	break;

#endif

    
#ifndef PERIDOT_WSTRING
case TokenExceptionType::BAD_STREAM:
	message = "The Lexer encountered a bad stream. This most likely means either that the stream has already been read to the end, in which case you should rewind it, or that it is an empty file, in which case, you should probably actually write a script first.";
	break;

#else
case TokenExceptionType::BAD_STREAM:
	message = L"The Lexer encountered a bad stream. This most likely means either that the stream has already been read to the end, in which case you should rewind it, or that it is an empty file, in which case, you should probably actually write a script first.";
	break;

#endif

    
#ifndef PERIDOT_WSTRING
default:
	message = "UNKNOWN ERROR";
	break;

#else
default:
	message = L"UNKNOWN ERROR";
	break;

#endif
    