text = File.open('Lexer.hpp','r')
ntext = '';
cases = '';
context = 'file'

pre = ""
text.each_line do |line|
  if line.include? 'enum TokenType' then
    context = 'tt'
    next
  end
  if context == 'tt' then
    if line.include? '}' then
      context = 'file'
      next
    end
    matches = line.scan(/([A-Z]+)/)
    cases += %Q[
#ifndef PERIDOT_WSTRING
#{pre}case TokenType::#{matches[0][0]}:\n#{pre}\tname = \"#{matches[0][0]}\";\n#{pre}\tbreak;\n
#else
#{pre}case TokenType::#{matches[0][0]}:\n#{pre}\tname = L\"#{matches[0][0]}\";\n#{pre}\tbreak;\n
#endif

    ]
  end
end
text.close
text = File.open('_token_type_to_name.hpp','w+') do |f|
  f.write cases
end
