input = File.open('../inputs/2018/day02-input.txt', 'r')

alphabet = "abcdefghijklmnopqrstuvwxyz"
twoLetters = 0
threeLetters = 0
input.each do |id|
    count = {}
    alphabet.chars.each do |c|
        count[c] = id.count(c)
    end
    if (count.has_value?(2)) then twoLetters += 1 end
    if (count.has_value?(3)) then threeLetters += 1 end
end

puts twoLetters * threeLetters

input.close
