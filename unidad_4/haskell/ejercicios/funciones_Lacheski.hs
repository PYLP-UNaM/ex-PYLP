
module FuncionesLacheski where

-- Funciones Simples

--1
sucesor :: Integer -> Integer
sucesor x = x + 1

--2
doble :: Integer -> Integer
doble x = 2*x

--3
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

--4
par :: Integer -> Bool
par x = x `mod` 2 == 0

--5
mayor :: (Integer, Integer) -> Integer
mayor (x,y) = if x<y then y else x

--6
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

--7
divMod :: (Integer, Integer) -> (Integer, Integer)
divMod (x,y) = (x `div` y, x `rem` y)

-- Funciones condicionales o recursivas

--8
factorial_1 :: Integer -> Integer
factorial_1 x = if (x == 1) then 1 else x * factorial_1(x-1) 

--9
factorial_2 :: Integer -> Integer
factorial_2 0 = 1
factorial_2 x = x * factorial_2(x-1)

--10
factorial_3 :: Integer -> Integer
factorial_3 0 = 1
factorial_3 x = facAux(1, x, 1) 

facAux :: (Integer, Integer, Integer) -> Integer
facAux(it, base, total) = if(it>base) then total else facAux(it+1,base,total*it)

--11
potencia :: (Integer, Integer) -> Integer
potencia (b, 0) = 1
potencia (b, e) = b * potencia(b, e-1)

-- Funciones de lista

--12
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud(xs)


--13
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

--14
maximo :: [Integer] -> Integer
maximo [] = -1
maximo (x:xs) = maximum(x:xs)

--15
push :: (Integer,[Integer]) -> [Integer]
push (a,[]) = [a]
push (a,x:xs) = x:xs ++ [a]

--16
customFilter(f,[]) = []
customFilter(f,x:xs) = if (f(x)==True) then x : customFilter(f, xs) else customFilter(f, xs)

--17
customMap (f, []) = []
customMap (f, x:xs) = f(x) : customMap(f, xs)

--18
indice (e, []) = -1
indice (e, x:xs) = indiceAux(e, x:xs, 0)
indiceAux (e, [], indice) = -1
indiceAux (e, x:xs, indice) = if(e == x) then indice else indiceAux(e, xs, indice+1)

--19
existe(e, []) = False
existe(e, x:xs) = if e == x then True else existe(e, xs)