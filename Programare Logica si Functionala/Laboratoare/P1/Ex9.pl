diferenta([],_,[]):-!.
diferenta([H|T], M, R):-exista(H,M),
                        !,
                        diferenta(T,M,R).
diferenta

% a. Sa se scrie un predicat care intoarce intersectia a doua multimi.
% intersectie(L: list, M: list, R: list)
% L - prima lista
% M - a doua lista
% R - intersectia celor doua liste
% Model de flux: (i, i, o) - determinist; (i, i, i) - determinist
intersectie([], _, []):-!.
intersectie([H|T], M, R1):- exista(H, M),
                            R1=[H|R],
                            !,
                            intersectie(T, M, R).
intersectie([_|T], M, R):- intersectie(T, M, R).


% exista(E: int, L: list)
% E - elementul cautat
% L - lista in care cautam elementul
% Model de flux: (i, i) - determinist (si (o, i) - determinist)
%                       false             , n = 0 (lista e vida)
% exista(e, l1l2..ln) = true              , elem = l1
%                       exista(e, l2..ln) , altfel
exista(E,[E|_]):-!.
exista(E,[_|T]) :- exista(E,T).


% b. Sa se construiasca lista (m, ..., n), adica multimea numerelor
% intregi din intervalul [m, n].
% interval(M: int, N: int, L:list)
% M - limita inferioara a intervalului
% N - limita superioara a intervalului
% L - lista in care se pun elementele
% Model de flux: (i, i, o) - determinist; (i, i, i) - determinist
%                     [], M > N
% interval(M, N, L) =
%                     [M] + interval(M + 1, N, L), altfel
interval(M, N, []):-M is N + 1, !.
interval(M, N, L1):-M =< N,
                  L1=[M|L],
                  M1 is M + 1,
                  interval(M1, N, L).











