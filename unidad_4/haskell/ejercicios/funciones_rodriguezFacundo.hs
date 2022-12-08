module Funciones where

-- 1. sucesor
sucesor :: Integer -> Integer
sucesor x = x + 1

pre :: Integer -> Integer
pre x = x - 1 

-- 2. doble 
doble :: Integer -> Integer 
doble x = x*2 

-- 3. cuadruple
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. par
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- 5. mayor
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x>=y then x else y

-- 6. division
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

-- 7. divisionResto

divisionResto :: (Integer, Integer) -> (Integer, Integer)
divisionResto (x,y) = (x `div` y, x `mod` y)

-- 8. factorial
factorial_a :: Integer -> Integer
factorial_a x = if ( x == 1 ) then 1
                else
                  x * factorial_a(x-1)

-- 9. factorial por patrones
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b x = x * factorial_b(x-1)

-- 10. factorial recursion no final
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = factorialAux(1, x, 1) 

factorialAux :: (Integer, Integer, Integer) -> Integer
factorialAux(it, base, tot) = if it > base then tot
                              else
                                factorialAux(it+1, base, tot*it)

-- 11. potencia
potencia_a :: (Integer, Integer) -> Integer
potencia_a (b,e) = if ( b == 0 && e==0 ) then -1
                  else if ( b == 0 ) then 0
                  else if ( e == 0 ) then 1
                  else b*potencia_a(b,e-1)

-- 11. potencia por patrones
potencia_b :: (Integer, Integer) -> Integer
potencia_b (0,0) = -1
potencia_b (b,0) = 1
potencia_b (0,e) = 0
potencia_b (b,e) = b*potencia_b(b,e-1)

-- 12. longitud
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 +  longitud(xs)

-- 13. sumatoria
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. maximo
maximo :: [Integer] -> Integer
maximo [] = -1
maximo (x:xs) = maximum(x:xs)

-- 15. push
push :: (Integer,[Integer]) -> [Integer]
push (a,[]) = [a]
push (a,x:xs) = x:xs ++ [a]

-- 16. customFilter
customFilter(f, []) = []
customFilter(f, x:xs) = if (f(x) == True) then
                         x : customFilter(f,xs)
                        else 
                          customFilter(f,xs)

-- 17. customMap
--customMap :: (f,[Integer]) -> [Integer]
customMap (f,[]) = []
customMap (f,x:xs) = f(x) : customMap(f, xs)

-- 18). indice
indice (e, []) = -1
indice (e, x:xs) = indiceAux(e, x:xs, 0)

indiceAux (e, [], indice) = -1
indiceAux (e, x:xs, indice) = if(e == x) then
                                        indice
                                else
                                        indiceAux(e, xs, indice + 1)

-- 19. existe
existe (e, []) = False
existe (e, x:xs) = if e == x then 
                	True
                   else
                      	existe(e, xs)
