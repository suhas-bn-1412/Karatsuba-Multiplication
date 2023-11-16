# Karatsuba-Multiplication
Implementation of Karatsuba Multiplication Algorithm in C

Gave very valuable experience in dynamic memory management and pointers concept in C

Abstract: Karatsuba algorithm is fast multiplication algorithm discovered by Anatoly Karatsuba in 1960. We implemented the Karatsuba fast multiplication algorithm for large integers.

Algorithm:
Let x and y be represented as n-digit strings in some base B. For any positive integer m less than n, we can write the two given numbers as

 x = x1 * B^m  + x0
 
 y = y1 * B^m  + y0


Where x0 and y0 are less than B^m. The product can be written as

 x * y =  (x1 B^m + x0)(y1 B^m + y0) =  z2 * B^2m  +  z1 * B^m  + z0

z0 = x1*y1

z1 = x1 * y0 + x0 * y1

z2 = x0 * y0

z1 can be calculated as z1 = (x0 + x1)*(y0 + y1)  - z2 - z0

Time complexity:

Recursive relation is given by
		
  T(n) = 3T(n/2) + cn + d

  T(n) = O(n^(log3 / log2)) 
  ~  O( n^1.585)



