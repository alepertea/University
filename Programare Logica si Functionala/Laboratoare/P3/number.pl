% general(N: integer; L: list)
% N - numarul de descompus
% L - lista cu descompunerile numarului N
% Model de flux: (i, o), (i, i), determinist
general(N, L):- findall(Rez, descompunere(N, Rez), L).

% descompunere(N: integer; R: list)
% N - numarul de descompus
% L - lista cu descompunerea numarului
% Model de flux: (i, o), (i, i), nedeterminist
descompunere(N, R):-N > 0,
                    N1 is N - 1,
                    lista(N1, L),
                    back(L, N, R, []).

% lista(N: integer; L: list)
% N - numarul pana la care generam lista
% L - lista rezultat
% Model de flux: (i, o), (i, i), determinist
lista(N, L) :- generareLista(N, [], L).

% Model matematic:
%                    lista                   , N = 0
% generareLista(N) =
%                    N + generareLista(N - 1), altfel
% generareLista(N: integer; R: list; L: list)
% N - numarul dupa care generam lista
% R - lista colectoare in care coletam elementele pana la N
% L - lista rezultat
% Model de flux: (i, i, o), (i, i, i), determinist
generareLista(0, L, L) :- !.
generareLista(N, R, L) :- N1 is N-1,
                          generareLista(N1, [N|R], L).

% Model matematic:
%                      1. l1                , n > 0
% candidat(l1l2..ln) =
%                      2. candidat(l2l3..ln), n > 0
% candidat(L: list; Elem: integer)
% L    - lista din care extragem candidatul
% Elem - elementul candidat extras
% Model de flux: (i, o) - nedeterminist
candidat([H|_], H).
candidat([_|T], Elem) :- candidat(T, Elem).


% Model matematic:
%                     0                      , n = 0
% suma(l1l2..ln, s) =
%                     suma(l2l3...ln, s + l1), altfel
% suma(L: list; Sum: integer)
% L   - lista input
% Sum - suma elementelor din lista
% Model de flux: (i, o), (i, i) - determinist
suma([], 0).
suma([H|T], Sum):- suma(T, Sum1),
                   Sum is Sum1 + H.

% Model matematic:
%                  1. Col, n > 0, eSolutie(Col), Col = {candidati}
% back(l1l2..ln) =
%                  2. back(l2l3..ln), n > 0, consecutiv(Col), Col =
%                  {candidati}
% back(L: list; N: integer; R: list; Col: list)
% L - lista candidatilor
% N - numarul la care facem descompunerea
% R - lista rezultat
% Col - lista colectoare
% Model de flux: (i, i, o, i) - nedeterminist
back(_, N, Col, Col) :- eSolutie(Col, N), !.
back(L, N, R, Col) :- candidat(L, E),
                      Col1 = [E|Col],
                      consecutiv(Col1),
                      back(L, N, R, Col1).

% consecutiv(L: list)
% L - lista pe care o verificam
% Model de flux: i, determinist
consecutiv([_]):- !.
consecutiv([H1,H2|_]) :- H2 =:= H1 + 1.

% eSolutie(L: list; N: integer)
% L - lista la care verificam ca e solutie
% N - numarul de care ne ajutam pentru suma
% Model de flux: (i, i), determinist
eSolutie(L, N) :- suma(L, S),
                  S =:= N.






