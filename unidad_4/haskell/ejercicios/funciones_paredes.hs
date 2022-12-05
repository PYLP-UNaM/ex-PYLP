module Funciones where

{- Funciones iniciales -}

-- 1. sucesor
sucesor :: Integer -> Integer
sucesor x = x + 1

pre :: Integer -> Integer
pre x = x - 1 

-- 2. doble 
doble :: Integer -> Integer
doble x = x+x


-- 3. Cuadruple de un numero
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Numero par
isPar :: Integer -> Bool
isPar x = x `rem` 2 == 0 

-- 5. Devuelve mayor
mayor :: (Integer, Integer) -> Integer
mayor (x,y) = if x>=y then x else y

-- 6. Division tupla
divisionTupla :: (Integer, Integer) -> Double
divisionTupla (x,y) = fromInteger(x) / fromInteger(y)

-- 7. Escribir una funcion que dada una tupla de enteros devuelva una tupla con la division entera como primer miembro y el resto como segundo miembro de la tupla
divisionResto :: (Integer, Integer) -> (Integer, Integer)
divisionResto (x,y) = (x `div` y,x `rem` y) 

-- 8. Factorial de un numero
factorial :: Integer -> Integer
factorial x = if (x==1) then 1 
                else
                    x*factorial(x-1)

-- 9. Factorial ajuste de patrones
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b 1 = 1
factorial_b 2 = 2
factorial_b x = x * factorial_b(x-1)

-- 10. Factorial recursion final
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = facAux(1, x, 1) 

facAux :: (Integer, Integer, Integer) -> Integer
facAux(it, base, total) = if(it>base) then total else facAux(it+1,base,total*it)

-- 11. Escribir una funcion que dada una tupla (base, exponente) devuelva la potencia exponente de la base.
potencia :: (Integer, Integer) -> Double
potencia (x,y) =  fromInteger(x) ** fromInteger(y)

-- 12. Longitud lista
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1+longitud(xs)

-- 13. Escribir una funcion que dada una lista de elementos devuelva la suma de los elementos de dicha lista. sumatoria
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. Escribir una funcion que devuelva el Maximo elemento de una lista maximo
maximo :: [Int] -> Int
maximo [] = 0
maximo (x:xs) = if (x < maximo(xs)) 
                then maximo(xs)
                else x

--15. Push el final
push (num, []) = [num]
push (num, x:xs) = x:push(num, xs)

-- 16. Custom Filter 
customFilter(f,[]) = []
customFilter(f,x:xs) = if (f(x)==True)then 
                            x:customFilter(f,xs)
                        else
                            customFilter(f,xs)

-- 17. CustomMap
customMap (f,[]) = []
customMap (f,x:xs) = f(x) : customMap(f, xs)

-- 18. indexOf
indexOf (num, []) = -1
indexOf (num, x:xs) = indexOfAux(num, x:xs, 0)

indexOfAux (num, [], index) = -1
indexOfAux (num, x:xs, index) = if(num == x) then
                                        index
                                else
                                        indexOfAux(num, xs, index + 1)

-- 19. exists
exists :: (Int, [Int]) -> Bool
exists (a,[]) = False
exists (a,x:xs) =   if (a == x)
                    then True
                    else exists(a,xs)
