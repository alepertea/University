; Model matematic:
; 							 []													 	  , n = 0
; substitutie_aux(l, e, p) = l														  , l este atom si l != e
;							 p1p2..pm												  , l este atom si l = e, p = p1p2..pm
; 							 substitutie(l1) + substitutie(l2) + ... + substitutie(ln), altfel, l = l1l2..ln
; Parametrii:
; l - lista data L
; e - elementul ce trebuie substituit E
; p - lista ce contine elementele cu care il voi substitui pe e
; EX: L = (1 2 (2 3) (2) 3 5 2), E = 2, L = (0 0) => (1 0 0 (0 0 3) (0 0) 3 5 0 0)
(defun substitutie_aux(L e P)
	(cond
		((null L) nil)
		((and (atom L) (not(eq L e))) (list L))
		((and (atom L) (eq L e)) P)
		(t (list (apply #'append (mapcar #'(lambda (L)
												(substitutie_aux L e P)
										   )L
								 )
				 )
			)
		)
	)
)

(defun substitutie(L e P)
	(car (substitutie_aux L e P))
)