import Data.Char

evalMuls :: String -> Int
evalMuls s = evalMuls' 0 False s
evalMuls' acc _ "" = acc
evalMuls' acc False str =
    if (take 7 str) == "don't()"
    then evalMuls' acc True (drop 7 str)
    else if (take 4 str) == "mul("
    then let bracket = drop 4 str
             num1 = read (takeWhile isDigit bracket) :: Int
             rest = dropWhile isDigit bracket
         in if head rest == ','
            then let num2 = read (takeWhile isDigit (drop 1 rest)) :: Int
                     rest2 = dropWhile isDigit (drop 1 rest)
                 in if head rest2 == ')'
                    then evalMuls' (acc + num1 * num2) False (drop 1 rest2)
                    else evalMuls' acc False rest2
            else evalMuls' acc False rest
    else evalMuls' acc False (drop 1 str)
evalMuls' acc True str =
    if (take 4 str) == "do()"
    then evalMuls' acc False (drop 4 str)
    else evalMuls' acc True (drop 1 str)

main = do
       file <- readFile "../inputs/2024/day03-input.txt"
       putStrLn $ show $ evalMuls file