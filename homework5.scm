;------------------------------------------------------------------------------;
; Developer---Cole Carter                                                      ;
; Course------CS3713-01                                                        ;
; Project-----Homework #5                                                      ;
; Due Date----October 29, 2024                                                 ;
;                                                                              ;
; This project uses Scheme functions to sort a list by following the concept   ;
; of the selection sort algorithm.                                             ;
;------------------------------------------------------------------------------;

;-----------------------------------------------------------;
; Name---smallest                                           ;
;                                                           ;
; This function finds and returns the smallest item in      ;
; a list.                                                   ;
;-----------------------------------------------------------;
(define (smallest lst)
  (cond ((null? (cdr lst)) (car lst))
        ((< (car lst) (smallest (cdr lst))) (car lst))
        (else (smallest (cdr lst)))
   )
)

;-----------------------------------------------------------;
; Name---remove                                             ;
;                                                           ;
; This function removes the given item from a list.         ;
;-----------------------------------------------------------;
(define (remove item lst)
  (cond ((null? lst) '())
        ((= (car lst) item) (cdr lst))
        (else (cons (car lst) (remove item (cdr lst))))
   )
)

;-----------------------------------------------------------;
; Name---selection                                          ;
;                                                           ;
; This function sorts a given list by following the         ;
; concept of the selection sort algorithm.                  ;
;-----------------------------------------------------------;
(define (selection lst)
  (cond ((null? lst) '())
        (else (cons (smallest lst) (selection (remove (smallest lst) lst))))
   )
)
