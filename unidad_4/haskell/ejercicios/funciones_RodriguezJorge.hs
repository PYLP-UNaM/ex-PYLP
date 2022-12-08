module Funciones where

{- Funciones simples -}

-- 1. Sucesor de un número entero.
sucesor :: Integer -> Integer
sucesor x = x + 1

-- 2. Doble de un número.
doble :: Integer -> Integer 
doble x = x * 2 

-- 3. Cuádruple de un número.
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Es par?
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- 5. Valor mayor entre una tupla.
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x >= y then x else y

-- 6. División de una tupla de enteros.
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

-- 7. División entera con resto.
divEnteroResto :: (Integer, Integer) -> (Integer, Integer)
divEnteroResto (x,y) = (x `div` y, x `rem` y)

{- Funciones condicionales o recursivas -}

-- 8. Factorial de un número.
factorial_A :: Integer -> Integer
factorial_A x = if ( x == 1 ) then 1
                else
                  x * factorial_A(x-1)

-- 9. Factorial con ajuste de patrones.
factorial_B :: Integer -> Integer
factorial_B 0 = 1
factorial_B x = x * factorial_B(x-1)

-- 10. Funcion anterior pero con una recursión final.
factorial_C :: Integer -> Integer
factorial_C 0 = 1
factorial_C x = factorialAux(1, x, 1) 

factorialAux :: (Integer, Integer, Integer) -> Integer
factorialAux(it, base, total) = if it > base then total
                              else
                                factorialAux(it + 1, base, total * it)

-- 11. Potencia.
potencia :: (Integer, Integer) -> Integer
potencia (base, 0) = 1
potencia (base, 1) = base
potencia (base, exponente) = base * potencia(base, exponente - 1)

{- Funciones de lista -}      

 -- 12. Longitud de una lista. 
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud (xs)

-- 13. Suma de los elementos de dicha lista.
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. Máximo elemento de una lista. 
maximo :: [Int] -> Int
maximo [] = 0
maximo (x:xs) = if (x < maximo(xs)) then maximo(xs) else x

-- 15. Lista con el elemento insertado al final.
push :: (Integer, [Integer]) -> [Integer]
push (e, []) = [e]
push (e, x:xs) = x : push(e, xs)

-- 16. Filtrado de elementos de una lista según un criterio dada en una función.
customFilter:: (a->Bool)->[a]->[a] 
customFilter p [] = [] 
customFilter p (a:y) = if (p a) then a:customFilter p y else customFilter p y 

-- 17. Escribir una funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista. `customMap`   
customMap (f, []) = []
customMap (f, x:xs) =f(x): customMap(f, xs)    

-- 18. Posición de un elemento.
indexOf (e, []) = -1
indexOf (e, x:xs) = indexOfAux(e, x:xs, 0)

indexOfAux (e, [], i) = -1
indexOfAux (e, x:xs, i) = if (e == x) then i
                          else 
                            indexOfAux (e, xs, i + 1)

-- 19. Existe elemento?
exists (e, []) = False
exists (e, x:xs) =  if (e == x) then True
                    else 
                      exists (e, xs)