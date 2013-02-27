
table = File.open("ascii.txt",'r')
table.each_line do |line|
  parts = line.split(/\t/)
  puts "char \t#{parts[3].gsub("\n",'')}\t\t=\t\t0x#{parts[2].gsub(" ",'')};"
end
