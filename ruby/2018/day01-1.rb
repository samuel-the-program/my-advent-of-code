input = File.open('../inputs/2018/day01-input.txt', 'r')

sum = 0
input.each do |line|
    sum += line.to_i
end
puts sum

input.close
