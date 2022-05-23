; a)
; Model matematic:
; 										[]											, n = 0
; eliminare(l1l2...ln, n, pozCurenta) =	eliminare(l2l3..ln, n, pozCurenta + 1) 		, pozCurenta = n
; 										l1 + eliminare(l2l3...ln, n, pozCurenta + 1), pozCurenta != n
(defun eliminare(lista n pozCurenta)
	(cond
		((null lista) nil)
		((= pozCurenta n) (eliminare (cdr lista) n (+ pozCurenta 1)))
		(t (cons (car lista) (eliminare (cdr lista) n (+ pozCurenta 1))))
	)
)

; Model matematic:
; elimin(l1l2..ln, nr) = eliminare(l1l2..ln, nr, 1)
(defun elimin(lista n)
	(eliminare lista n 1)
)


; b)
; Model matematic:
;									 colectoare							, n = 0
; invers_aux(l1l2..ln, colectoare) = 
;									 invers_aux(l2..ln, l1 + colectoare), altfel
(defun invers_aux (lista col)
	(cond
		((null lista) col)
		(T (invers_aux (cdr lista) (cons (car lista) col)))
	)
)

; Model matematic:
; invers(l1l2..ln) = invers_aux(l1l2..ln, [])
(defun invers(lista)
	(invers_aux lista ())
)

; Model matematic:
; succesor(l1l2..ln) = invers(succesor_aux(invers(l1l2..ln), 1))
(defun succesor(lista)
	(invers (succesor_aux (invers lista) 1))
)

; Model matematic:
;								[]										, n = 0
; succesor_aux(l1l2..ln, tr) =  (tr + l1) % 10 + succesor_aux(l2..ln, 1), tr + l1 > 9
;								(tr + l1) + succesor_aux(l2..ln, 0)		, altfel
(defun succesor_aux (lista tr)
	(cond
		((null lista) nil)
		((> (+ tr (car lista)) 9) (cons (mod (+ tr (car lista)) 10) (succesor_aux (cdr lista) 1)))
		(t (cons (+ tr (car lista)) (succesor_aux (cdr lista) 0)))
	)
)


; d)
; Model matematic:
; 						true				, n = 0
; multime(l1l2...ln) = 	false				, exista(l1, l2l3..ln) = true
; 						multime(l2l3..ln)	, altfel
(defun multime(lista)
	(cond
		((null lista) t)
		((exista (car lista) (cdr lista)) nil)
		(t (multime (cdr lista)))
	)
)

; Functie de aparitie a unui element intr-o lista liniara data
; Model matematic:
;						   false					, n = 0 	
; exista(elem, l1l2..ln) = true						, elem = l1
;						   exista(elem, l2l3..ln)	, altfel
(defun exista(elem lista)
	(cond
		((null lista) nil)
		((eql elem (car lista)) t)
		(t (exista elem (cdr lista)))
	)
)

; c)
; Model matematic:
;					[]							, n = 0
; atomi(l1l2..ln) = l1 + atomi(l2..ln)			, l1 e atom
;					atomi(l1) + atomi(l2..ln)	, altfel
(defun atomi(lista)
	(cond
		((null lista) nil)
		((atom (car lista)) (cons (car lista) (atomi (cdr lista))))
		(t (append (atomi (car lista)) (atomi (cdr lista))))
	)
)

; Functie care imi ia o lista si o transforma in multime
; Model matematic:
;							 			 colectoare								, n = 0
; creeazaMultime(l1l2..ln, colectoare) = creeazaMultime(l2..ln, l1 + colectoare), exista(l1, colectoare) = false 
;										 creeazaMultime(l2..ln, colectoare)		, altfel
(defun creeazaMultime(lista col)
	(cond
		((null lista) col)
		((not(exista (car lista) col)) (creeazaMultime (cdr lista) (cons (car lista) col)))
		(t (creeazaMultime (cdr lista) col))
	)
)

; Model matematic:
; multimeAtomi(l1l2..ln) = creeazaMultime(atomi(l1l2..ln), [])
(defun multimeAtomi(lista)
	(creeazaMultime (atomi lista) ())
)















