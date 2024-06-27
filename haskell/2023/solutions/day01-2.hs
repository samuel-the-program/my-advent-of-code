import Data.Char
import Data.List as L

isSuffix :: String -> String -> Bool
isSuffix s x = drop (length x - length s) x == s 

digits = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
firstDigit :: String -> [String] -> Char
firstDigit [] _ = '0'
firstDigit all@(_:xs) ys
   | digit == Nothing = firstDigit xs ys
   | otherwise        = getDigit (maybe "0" id digit)
   where digit = find (\d -> isPrefixOf d all) ys
         getDigit x = if length x == 1 then x !! 0 else intToDigit (maybe 0 id (findIndex (==x) ys) + 1)

revDigits = ["eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
lastDigit :: String -> [String] -> Char
lastDigit x = firstDigit (reverse x)

calibration :: String -> Int
calibration x = read [firstDigit x digits, lastDigit x revDigits]

solution :: String -> String
solution x = show $ sum $ L.map calibration (L.lines x)

main = do
       file <- readFile "../inputs/2023/day01-input.txt"
       putStrLn $ solution file
       