input = File.open('../inputs/2018/day01-input.txt', 'r')

nums = input.readlines.map{|x| x.chomp.to_i}

freqs = []
cur_freq = 0;
num_i = 0
while not freqs.include?(cur_freq) do
    freqs << cur_freq;
    cur_freq += nums[num_i]
    num_i = (num_i + 1) % nums.length
end

puts cur_freq;

input.close
