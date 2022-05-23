/* Sa se inlocuiasca toate aparitiile unui element dintr-o lista cu un alt element
 * a.
 * Modelul matematic:
 *                           []                            , n = 0
 * subst(l1l2..ln, e1, e2) = [e2] + subst(l2l3..ln, e1, e2), l1 = e1
 *                           subst(l2l3..ln, e1, e2)       , altfel
 * subst(L: list; E1: int; E2: int; R: list)
 * L  - lista initiala
 * E1 - elementul ce trebuie substituit
 * E2 - elementul cu care substituim
 * R  - lista rezultat
 * Model de flux: (i, i, i, i) - determinist; (i, i, i, o) - determinist
*/
subst([], _, _, []):-!.
subst([H|T], E1, E2, R1):- H == E1,
                           !,
                           R1 = [E2|R],
                           subst(T, E1, E2, R).

subst([H|T], E1, E2, R1):- R1 = [H|R],
                           subst(T, E1, E2, R).


/*
 * b. Se da o lista eterogena, formata din numere intregi si liste de numere intregi. 
 * Se cere ca toate aparitiile elementului maxim (dintre valorile intregi ale listei) sa fie inlocuite in fiecare sublista cu maximul sublistei respective.
*/

/*
 * Determina elementul maxim dintr-o lista eterogena.
 * Modelul matematic:
 *                        max                   , n = 0
 * maxim(l1l2..ln, max) = maxim(l2l3..ln, l1)  , l1 > max
 *                        maxim(l2l3..ln, max) , altfel
 * maxim(L: list, Max0: int, Max: int)
 * L    - lista eterogena in care cautam elementul maxim
 * Max0 - maximul intermediar
 * Max  - maximul listei
 * Model de flux: (i, i, i) - determinist, (i, i, o) - determinist
 * maxLista(L: list, Max: int)
 * L   - lista in care cautam elementul maxim
 * Max - elementul maxim
 * Model de flux: (i, i) - determinist, (i, o) - determinist
*/
maxLista([H|T], Max):- maxim(T, H, Max).

maxim([], Max, Max):-!.
maxim([H|T], Max0, Max):- number(H),
                          !,
                          Max1 is max(H, Max0),
                          maxim(T, Max1, Max).
maxim([_|T], Max0, Max):- maxim(T, Max0, Max).


/*
 * Model matematic:
 *                            [], n = 0
 * subst_aux(l1l2..ln, max) = subst(l1, max, maxSublista) +
 *                            subst_aux(l2l3..ln, max), l1 e lista
 *                            subst_aux(l2l3..ln, max), altfel
 * subst_aux(L: list, M: int, R: list)
 * L - lista initiala, eterogena
 * M - maximul listei eterogene
 * R - lista rezultat
 * Model de flux: (i, i, i) - determinist, (i, i, o) - determinist
 */

substLista(L, R):- maxLista(L, M),
                   subst_aux(L, M, R).

subst_aux([], _, []):-!.
subst_aux([H|T], M, R1):- is_list(H),
                         !,
                         maxLista(H,Max),
                         subst(H, M, Max, Rez),
                         R1=[Rez|R],
                         subst_aux(T, M, R).
subst_aux([H|T], M, R1):- R1=[H|R],
                          subst_aux(T, M, R).












