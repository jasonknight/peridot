exception_messages = {}

exception_messages["UNRECOGNIZED_ENTITY"] = %Q[The Lexer encountered an unrecognized entity '%s' at line %d column %d. \
This is most likely caused by a set of TokenTypeDictionary's that are too restrictive considering the input. It may \
also simply be an erroneus char value.]

exception_messages["BAD_STREAM"] = %Q[The Lexer encountered a bad stream. This most likely means either that the stream \
has already been read to the end, in which case you should rewind it, or that it is an empty file, in which case, you \
should probably actually write a script first.]

text = File.open('Lexer.hpp','r')
ntext = '';
cases = '';
context = 'file'

pre = ""
text.each_line do |line|
  if line.include? 'enum TokenExceptionType' then
    context = 'tt'
    next
  end
  if context == 'tt' then
    if line.include? '}' then
      context = 'file'
      next
    end
    matches = line.scan(/([A-Z_]+)/)
    cases += %Q[
#ifndef PERIDOT_WSTRING
#{pre}case TokenExceptionType::#{matches[0][0]}:\n#{pre}\tmessage = \"#{exception_messages[matches[0][0]]}\";\n#{pre}\tbreak;\n
#else
#{pre}case TokenExceptionType::#{matches[0][0]}:\n#{pre}\tmessage = L"#{exception_messages[matches[0][0]]}\";\n#{pre}\tbreak;\n
#endif

    ]
  end
end
text.close
text = File.open('_token_exception_to_msg.hpp','w+') do |f|
  f.write cases
  f.write %Q[
#ifndef PERIDOT_WSTRING
#{pre}default:\n#{pre}\tmessage = \"UNKNOWN ERROR\";\n#{pre}\tbreak;\n
#else
#{pre}default:\n#{pre}\tmessage = L\"UNKNOWN ERROR\";\n#{pre}\tbreak;\n
#endif
    ]

end
