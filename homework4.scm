;------------------------------------------------------------------------------;
; Developer---Cole Carter                                                      ;
; Course------CS3713-01                                                        ;
; Project-----Homework #4                                                      ;
; Due Date----October 15, 2024                                                 ;
;                                                                              ;
; This project includes definitions for various functions as described below.  ;
;------------------------------------------------------------------------------;

;-----------------------------------------------------------;
; Name---factorial                                          ;
;                                                           ;
; This function calculates the factorial of a given number. ;
;-----------------------------------------------------------;
(define (factorial n)
  (cond
    ;handles all base cases involving negatives and zero, as well as being the stopping condition.
    ((< n 2) 1)
    ;recursively calculate the factorial of n.
    (else (* n (factorial (- n 1))))
   )
)

;---------------------------------------------------------------;
; Name---power                                                  ;
;                                                               ;
; This function calculates the exponentiation for a number with ;
; a given base and exponent.                                    ;
;---------------------------------------------------------------;
(define (power base exponent)
  (cond
    ;base case.
    ((= exponent 0) 1)
    ;if exponent is negative, call power with inverted exponent. once it returns, divide 1 by the answer. 
    ((< exponent 0) (/ 1.0 (power base (- exponent))))
    ;recursively multiply base by itself while also decreasing exponent to "count" how many times we do it.
    (else (* base (power base (- exponent 1)))) 
   )
)

;---------------------------------------------------------------;
; Name---largest                                                ;
;                                                               ;
; This function finds and returns the largest number in a list  ;
; by comparing two items at a time until it finds the largest.  ;
;---------------------------------------------------------------;
(define (largest nlist)
  (cond
    ;if the list is empty, return 0.
    ((null? nlist) 0)
    ;if the list has only 1 number, return that number.
    ((null? (cdr nlist)) (car nlist))
    ;if car is less than cadr, we can "discard" car by calling largest with the cdr.
    ((< (car nlist) (cadr nlist)) (largest (cdr nlist)))
    ;if car is greater than cadr, "discard" cadr by calling largest with car and the cddr.
    (else (largest (cons (car nlist) (cddr nlist)))) 
   )
)