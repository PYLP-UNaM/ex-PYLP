module Funciones where
-- 1. Sucesor de..
sucesor::Integer -> Integer
sucesor x = x + 1

-- 2. Doble de..
doble::Integer -> Integer
doble x = x * 2

-- 3. Cuádruple de..
cuadruple::Integer -> Integer
--cuadruple x = x * 4
-- reutilizando la función doble
cuadruple x = doble(doble(x))

-- 4. Es Par...
esPar::Integer -> Bool
esPar x = x `mod` 2 == 0

-- 5. Es Mayor...
esMayor::(Integer,Integer) -> Integer
esMayor(x,y) = if x >= y then x else y

-- 6. División...
division::(Integer,Integer) -> Double
division(x,y) = fromInteger(x) / fromInteger(y)

-- 7. División con resto
divResto::(Integer,Integer) -> (Integer,Integer)
divResto(x,y)=(truncate(fromInteger(x)/fromInteger(y)),x `mod` y)

-- 8. Factorial
factorialSimple::Integer -> Integer
factorialSimple x = if (x==1)then 1 else x * factorialSimple(x-1)

-- 9. Factorial con ajuste
factorialAjuste::Integer -> Integer
factorialAjuste 0 = 1
factorialAjuste x = x * factorialSimple(x-1)

-- 10. Factorial con recursión final
factorialAjusteFin::(Integer,Integer,Integer) -> Integer
factorialAjusteFin (i,x,total)= if i > x then total else factorialAjusteFin(i+1, x, total*i) 

-- 11. Potencia
potencia::(Integer,Integer) -> Integer
potencia(base, exponente)= if (exponente == 0) then 1 else base*potencia(base,exponente-1)

-- 12. Longitud Lista
longitud::[Integer]-> Integer
longitud [] = 0 
longitud (x:z) = 1 + longitud (z) -- ejecutar: longitud[1,3,5,6] resul- 4

-- 13. Suma de elementos de la lista
sumaL::[Integer] -> Integer
sumaL [] = 0
sumaL (x:z) = x + sumaL(z) 

-- 14. Máximo elemento de la lista
maximoL::[Integer] -> Integer
maximoL [] = 0
maximoL(x:z) = esMayor(x,maximoL(z))

-- 15. Inserción al final de la lista
push (nItem, []) = [nItem] 
push (nItem, x:xs) = x:push(nItem, xs)  -- ejecutar: push(1,[3,4,5])  resultado: [3,4,5,1]

-- 16. Filtro en lista  ** No funciona **
customFilter:: (a->Bool)->[a]->[a] 
customFilter p [] = [] 
customFilter p (a:y) = if (p a) then a:customFilter p y else customFilter p y 
-- ejecución: customFilter (>3) [1,3,5,4,2,6,1]  resultado: [5,4,6]

-- 17. Función Map
customMap :: (a -> b) -> [a] -> [b]
customMap _ [] = []
customMap f (x:xs) = f(x):customMap f(xs) 
-- ejecución: CustomMap (*2) [3,4,7]  resultado: [6,8,14]

-- 18. Posición en la lista
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
-- ejecución: indexOf(2,[1,2,3,4,5])   resultado: 2

-- 19. Si elemento existe en la lista
existe :: (Integer, [Integer]) -> Bool
existe (e,[]) = False
existe (e,x:z) =   if (e == x) then True else existe(e,z)
-- ejecución: existe(2,[3,4,5])  resultado: False no se encuentra en la lista
