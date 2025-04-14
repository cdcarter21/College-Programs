%%=========================================================================
%% Developer---Cole Carter
%% Course------CS3713
%% Project-----Homework #7
%% Due Date----December 3, 2024
%%
%% This project utilizes Prolog list manipulation to emulate the Selection
%% Sort algorithm from imperative languages. 
%%=========================================================================

%%=========================================================================
%% Selection Sort a list of numbers. Uses smallest and remove.
%% I was having issues naming the predicate "sort" because it was saying
%% I was rewriting a built-in. 
%%=========================================================================
ssort([], []).
ssort(L, [M|R]) :- smallest(L, M),           
                   remove(M, L, L1),    
                   ssort(L1, R).  

%%=========================================================================
%% Finds the smallest element in the list X. 
%%=========================================================================
smallest([X], X).
smallest([H|T], H) :- smallest(T, MinTail),
                      H =< MinTail.
smallest([H|T], MinTail) :- smallest(T, MinTail),
                            H > MinTail.

%%=========================================================================
%% Removes the specified element from the list X.  
%%=========================================================================
remove(_, [], []).
remove(X, [X|T], T).
remove(X, [H|T], [H|Result]) :- X \= H,
                                remove(X, T, Result).



