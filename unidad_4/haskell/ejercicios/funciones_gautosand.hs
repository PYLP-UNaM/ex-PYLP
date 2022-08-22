module Funciones where

{- Funciones iniciales -}

-- 1. sucesor
sucesor :: Integer -> Integer
sucesor 2 = 4
sucesor 4 = 8 
sucesor x = x + 1

pre :: Integer -> Integer
pre x = x - 1 

-- 2. doble 
doble :: Integer -> Integer 
doble x = x*2 
-- 3.
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))
-- 4.
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

isMayor :: Integer -> Bool
isMayor x = if x>= 18 then True else False
-- 5.
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x>=y then x else y
-- 6.
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)
-- 7.
divisionyresto :: (Integer, Integer) -> (Integer, Integer)

divisionyresto (x,y) =(truncate(fromInteger(x)/fromInteger(y)),x `mod` y)


-- 8.
factorial_a :: Integer -> Integer
factorial_a x = if ( x == 1 ) then 1
                else
                  x * factorial_a(x-1)
--9.
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b x = x * factorial_b(x-1)

--10.
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = factorialAux(1, x, 1) 

factorialAux :: (Integer, Integer, Integer) -> Integer
factorialAux(it, base, tot) = if it > base then tot
                              else
                                factorialAux(it+1, base, tot*it)
--11.
potencia::(Integer,Integer)->Integer
potencia(b,e)=if e == 0 then 1 
        else b*potencia(b,e-1)

--12.
longitud :: [Integer] -> Integer
longitud [] = 0 
longitud (x:xs) = 1 + longitud(xs)
--13.                         
sumatoria :: [Integer] -> Integer
sumatoria [] = 0 
sumatoria (x:xs) = x + sumatoria(xs)
--14. 
maximo:: [Integer] -> Integer
maximo [] = 0 
maximo (x:xs) = mayor(x, maximo(xs))
--15. 
push (z, []) = [z]
push (z, x:xs) = x:push(z, xs)
--16.
customFilter(f, []) = []
customFilter(f, x:xs) = if (f(x)== True)then
                          x : customFilter(f, xs)
                        else  
                          customFilter(f, xs)
--17.
customMap(f, []) = []
customMap(f, x:xs) =f(x) : customMap(f, xs)

--18.

indexOftotal(v, x:xs,total) = if (longitud(xs)== 0) then
                          (if (x==v)then
                          1
                            else -1*total+ -1)
                        else  
                          (if (x==v)then
                          1
                            else 
                            1+indexOftotal(v, xs,total) )                        
indexOf::(Integer,[Integer]) ->Integer

indexOf(v, x:xs) = indexOftotal(v, x:xs,longitud(xs))

--19.
exists :: (Integer, [Integer]) -> Bool
exists (v,[]) = False
exists (v,x:xs) =   if (v == x)
                    then True
                    else exists(v,xs)

