input = File.open('../inputs/2018/day02-input.txt', 'r')

input.each do |id1|
    input.each do |id2|
        diffs = id1.chars.select.with_index do |val, i|
            val != id2[i]
        end
        if diffs.length == 1
            d = id1.chars.select.with_index do |val, i|
                val == id2[i]
            end
            puts d.join
        end
    end
end

input.close
