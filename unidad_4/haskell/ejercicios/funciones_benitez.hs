module Funciones where

{-------------------------- FUNCIONES SIMPLES --------------------------}

-- 1. Sucesor
sucesor :: Integer -> Integer
sucesor x = x + 1

-- 2. Doble 
doble :: Integer -> Integer 
doble x = x*2 

-- 3. Cuadruple
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))

-- 4. Es par
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- 5. Mayor de una tupla
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x>=y then x else y

-- 6. Division de una tupla
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)

-- 7. Funcion que dada una tupla de enteros devuelva una tupla con la division entera como primer miembro y el resto como segundo miembro de la tupla
division_mod :: (Integer, Integer) -> (Integer, Integer)
division_mod (x,y) = (x `div` y, x `mod` y)

{-------------------------- FUNCIONES CONDICIONALES O RECURSIVAS --------------------------}

-- 8. Hacer una función recursiva que devuelva el factorial de un numero.
factorial :: Integer -> Integer
factorial x 
	| x < 0 = 0
	| x == 0 = 1
	| otherwise = x * factorial(x - 1)

-- 9. Función anterior aplicando ajuste de patrones
factorial_patrones :: Integer -> Integer
factorial_patrones 0 = 1
factorial_patrones x = x * factorial_patrones(x - 1)

-- 10. Escribir la funcion anterior pero con recursion final
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = facAux(1, x, 1) 

facAux :: (Integer, Integer, Integer) -> Integer
facAux(it, base, total) = if (it > base) then total else facAux(it + 1, base,total * it)

-- 11. Potencia
potencia :: (Double, Integer) -> Double
potencia (b, e)
	| e < 0 = potencia(1/b,(-e))
	| e == 0 = 1/1
	| otherwise = multiplicar b e b
  		where multiplicar x z y = if z == 1 then y
  			else multiplicar x (z-1) (x * y)

{-------------------------- FUNCIONES DE LISTA --------------------------}

-- 12. Longitud
longitud :: [Integer] -> Integer
longitud [] = 0
longitud (x:xs) = 1 + longitud(xs)

-- 13. Sumatoria
sumatoria :: [Integer] -> Integer
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria(xs)

-- 14. Máximo
maximo :: [Int] -> Int
maximo [] = 0
maximo (x:xs) = if (x < maximo(xs)) then maximo(xs) else x

-- 15. Escribir una funcion que dada una lista y un numero. devuelva la lista con el elemento insertado al final. push
push (a, []) = [a]
push (a, x:xs) = x:push(a, xs)

-- 16. Escribir una funcion que dada una lista, filtre los elementos de la lista segun un criterio dada en una funcion. customFilter
customFilter(f, []) = []
customFilter(f, x:xs) = if (f(x)) then x : customFilter(f, xs) else customFilter(f, xs)

-- 17. Escribir una funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista. customMap
customMap (f,[]) = []
customMap (f,x:xs) = f(x) : customMap(f, xs)

-- 18) Funcion que pasada una un valor y una lista, devuelve la posicion en donde se encontro dicho elemento o -1 si no fue hallado. `indexOf`
indexOf (e, []) = -1
indexOf (e, x:xs) = index_aux(e, x:xs, 0)

index_aux (e, [], index) = -1
index_aux (e, x:xs, index) = if(e == x) then index else index_aux(e, xs, index + 1)

-- 19) Funcion que pasado un valor y una lista, devuelve Verdadero o Falso segun si el elemento existe en la lista. `exists`
exists (e, []) = False
exists (e, x:xs) = if e == x then True else exists(e, xs)