module Funciones where


-- ## Funciones simples

-- 1. sucesor
sucesor :: Integer -> Integer
sucesor 2 = 4
sucesor 4 = 8 
sucesor x = x + 1

-- predecesor
pre :: Integer -> Integer
pre x = x - 1 

-- 2. doble 
doble :: Integer -> Integer 
doble x = x*2 

-- 3. cuadruple de un número usando composición de funciones
cuadruple :: Integer -> Integer
cuadruple x = doble(doble(x))


-- 4. Es par
isPar :: Integer -> Bool
isPar x = x `mod` 2 == 0

-- Si un número es mayor o igual a 18 devuelve true de lo contrario devuelve false
isMayor :: Integer -> Bool
isMayor x = if x>= 18 then True else False

-- 5. Dada una tupla de números enteros, devuelve el mayor
mayor :: (Integer, Integer) -> Integer
mayor (x, y) = if x>=y then x else y

-- 6. División de una tupla de enteros (tenemos que castear usando la función fromInteger() )
division :: (Integer, Integer) -> Double
division (x,y) = fromInteger(x) / fromInteger(y)



-- ## Funciones condicionales o recursivas

--8 Factorial de un número
factorial_a :: Integer -> Integer
factorial_a x = if ( x == 1 ) then 1
                else
                  x * factorial_a(x-1)

-- 7. Escribir una funcion que dada una tupla de enteros devuelva una tupla con la division entera como primer miembro y el resto como segundo miembro de la tupla
--div devuelve la división entera
--rem devuelve el resto de la división
divisionResto :: (Integer, Integer) -> (Integer, Integer)
divisionResto (x,y) = (x `div` y,x `rem` y) 



-- 9. Factorial de un número usando ajuste de patrones
factorial_b :: Integer -> Integer
factorial_b 0 = 1
factorial_b x = x * factorial_b(x-1)

-- 10. Factorial con recursión final usamos una función auxiliar
factorial_c :: Integer -> Integer
factorial_c 0 = 1
factorial_c x = factorialAux(1, x, 1) 

factorialAux :: (Integer, Integer, Integer) -> Integer
factorialAux(it, base, tot) = if it > base then tot
                              else
                                factorialAux(it+1, base, tot*it)


-- 11. Dada una tupla `(base, exponente)` devuelva la potencia exponente de la base.
potencia :: (Integer, Integer) -> Integer
potencia (b, 0) = 1
potencia (b, e) = b * potencia(b, e-1)

-- ## Funciones de lista

-- 12. Devuelve la longitud de una lista de cualquier tipo de elementos (polimorfismo) a minusculas representa cualquier tipo 
-- de datos en Haskell incluyendo tipos definidos por el usuario
longitud :: [a] -> Integer
longitud [] = 0 
longitud (x:xs) = 1 + longitud(xs)


-- 13. Sumatoria de elementos de una lista
suma :: [Integer] -> Integer
suma [] = 0
suma (primero:resto) = primero + suma(resto)


-- 14. Escribir una funcion que devuelva el Maximo elemento de una lista
maximo :: [Integer] -> Integer
maximo [] = 0
maximo (x:xs) = if (x < maximo(xs)) 
                then maximo(xs)
                else x
                
                
-- 15. inserta un elemento al final de una lista, polimorfica, lista y elemento pasados de cualquier tipo
alFinal :: (a, [a]) -> [a]
alFinal (e,[]) = [e]
alFinal(e,primero:resto) = primero : alFinal(e,resto)



-- 16. una función que dada una lista filtre los elementos de la lista segun un criterio dada en una funcion. `customFilter`
customFilter(f, []) = []
customFilter(f, x:xs) = if (f(x)== True)then
                          x : customFilter(f, xs)
                        else  
                          customFilter(f, xs)
                          
-- 17. Escribir una funcion que dada una funcion y una lista, aplique la funcion a todos los elementos de la lista. `customMap`
-- función map es una función primitiva de Haskell, en éste caso aplica la función doble a cada elemento de la lista y devuelve esa lista
--  map doble [2,3,4,5]
-- [4,6,8,10]

customMap (f, []) = []
customMap (f, x:xs) = f(x) : customMap(f, xs)


--18 Escribir una funcion que pasado un valor y una lista, devuelva la posicion en donde se encontro dicho elemento o -1 si no fue hallado. `indexOf`
indexOf (e, []) = -1
indexOf (e, x:xs) = indexOfAux(e, x:xs, 0)
indexOfAux (e, [], indexOf) = -1
indexOfAux (e, x:xs, indexOf) = if(e == x) then indexOf else indexOfAux(e, xs, indexOf+1)

--19 Escribir una funcion que pasado un valor y una lista, devuelva Verdadero o Falso segun si el elemento existe en la lista. `exists`
exist(e, []) = False
exist(e, x:xs) = if e == x then True else exist(e, xs)























