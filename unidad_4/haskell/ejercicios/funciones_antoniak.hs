module Funciones where

{- Funciones iniciales -}

-- 1. Sucesor
sucesor :: Integer -> Integer
sucesor x = x + 1

-- 2. Doble 
doble :: Integer -> Integer 
doble x = x * 2

-- 3. Cuadruple
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Es par
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- 5. Mayor
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x > y then x else y

-- 6. Division exacta
divExacta :: (Integer, Integer) -> Double
{-
	fromInteger se utiliza para
	evitar devolver un tipo fraccionario
-}
divExacta (x,y) = fromInteger(x) / fromInteger(y)

-- 7. Division entera con resto
divEntera :: (Integer, Integer) -> (Integer, Integer)
{-
	quot y rem son mas adecuados que
	div y mod, se justifica en los
	casos que el dividendo y el divisor
	difieren en los signos.
-}
divEntera (x,y) = (x `quot` y, x `rem` y)

{- Funciones condicionales o recursivas -}

-- 8. Factorial (con guardias)
factorial :: Integer -> Integer
factorial x 
	| x < 0 = 0
	| x == 0 = 1
	| otherwise = x * factorial(x-1)

-- 9. Factorial con ajuste de patrones
factorialA :: Integer -> Integer
factorialA 0 = 1
factorialA x = if x < 0 then 0
		else x * factorialA(x-1)

-- 10. Factorial con recursion final
factorialR :: Integer -> Integer
factorialR x = if x < 0 then 0
		else recurFin x 1
  		where recurFin n y = if n == 0 then y
	  		else recurFin (n - 1) (n * y)

-- 11. Potencia
potencia :: (Double, Integer) -> Double
potencia (b, e)
	| e < 0 = potencia(1/b,(-e))
	| e == 0 = 1/1
	| otherwise = multiplicar b e b
  		where multiplicar x z y = if z == 1 then y
  			else multiplicar x (z-1) (x * y)

{- Funciones de lista -}

-- 12. Longitud de lista
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud(xs)

-- 13. Sumatoria de lista
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. Maximo
maximo :: [Integer] -> Maybe Integer
maximo [] = Nothing
maximo (x:xs) = Just(maxi x xs)
		where maxi m (l:ls) = if ls == []
			then mayor (m, l)
			else maxi (mayor(m, l)) ls

-- 15. Push
push :: ([Integer], Integer) -> [Integer]
push (l,n) = l ++ [n]

-- 16. Filtro personalizado
customFilter :: ([Integer], (Integer -> Bool)) -> [Integer]
customFilter ([],f) = []
customFilter (x:xs, f) = if f x then ([x] ++ customFilter(xs,f))
				else customFilter(xs,f)

-- 17. Mapeo personalizado
customMap :: ([Integer], (Integer -> Integer)) -> [Integer]
customMap ([],f) = []
customMap ((x:xs),f) = [f x] ++ customMap(xs,f)

-- 18. Lugar de elemento
indexOf :: (Integer, [Integer]) -> Integer
indexOf (v, []) = -1
indexOf (v, (l:ls)) = lugar 0 v (l:ls)
			where lugar n x (y:ys) = if x == y then n
				else if ys == [] then -1
					else lugar (n+1) x ys

-- 19. Existencia de elemento
exists :: (Integer, [Integer]) -> Bool
exists (v, []) = False
exists (v, (l:ls)) = existe v (l:ls)
			where existe x (y:ys) = if x == y then True
				else if ys == [] then False
					else existe x ys
