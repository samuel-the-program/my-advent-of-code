import Data.Char
import Data.List as L

firstDigit :: String -> Char
firstDigit x = maybe '0' id (L.find isDigit x)

lastDigit :: String -> Char
lastDigit x = firstDigit $ L.reverse x

calibration :: String -> Int
calibration x = read [firstDigit x, lastDigit x]

solution :: String -> String
solution x = show $ sum $ L.map calibration (L.lines x)

main = do
       file <- readFile "../inputs/2023/day01-input.txt"
       putStrLn $ solution file
       