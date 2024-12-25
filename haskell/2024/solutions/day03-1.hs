import Data.Char

evalMuls :: String -> Int
evalMuls s = evalMuls' 0 s
evalMuls' acc "" = acc
evalMuls' acc str = 
    if (take 4 str) == "mul("
    then let bracket = drop 4 str
             num1 = read (takeWhile isDigit bracket) :: Int
             rest = dropWhile isDigit bracket
         in if head rest == ','
            then let num2 = read (takeWhile isDigit (drop 1 rest)) :: Int
                     rest2 = dropWhile isDigit (drop 1 rest)
                 in if head rest2 == ')'
                    then evalMuls' (acc + num1 * num2) (drop 1 rest2)
                    else evalMuls' acc (rest2)
            else evalMuls' acc (rest)
    else evalMuls' acc (drop 1 str)


solution :: [String] -> Int
solution s = sum $ map evalMuls s

main = do
       file <- readFile "../inputs/2024/day03-input.txt"
       putStrLn $ show $ solution $ lines file