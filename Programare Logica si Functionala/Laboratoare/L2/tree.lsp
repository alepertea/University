; (A 2 B 0 C 2 D 0 E 0) => (A (B) (C (D) (E)))
;
; Model matematic:
;					  []					, n = 0
;					  [l1 + convert(l3..ln)], l2 > 0
; convert(l1l2..ln) = [l1] + convert(l3..ln), l2 = 0
;					  convert(l3..ln)		, altfel

(defun convert_aux(lista)
  (cond
    ((null lista) nil)
    ((> (cadr lista) 0) (list (append (list (car lista)) (convert_aux(cddr lista)))))
    ((= (cadr lista) 0) (append (list (list (car lista))) (convert_aux(cddr lista))))
    (t (convert_aux(cddr lista)))
  )
)

(defun convert(lista)
	(car (convert_aux lista))
)