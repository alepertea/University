class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)
    
def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)

'''
functie care returneaza primul nod dintr-o lista
'''
def prim(lista):
    return lista.prim


'''
functie care determina lungimea unei liste
'''
def lungime(nod, i):
    if nod == None:
        return i
    else:
        return lungime(nod.urm, i + 1)

'''
Modelul matematic:
                            {elem l2..ln}, c == i
subst(l1..ln, i, c, el) =
                            subst(l2..ln, i, c + 1, el), c != i
'''

def subst(lista, i, c, el):
    if lungime(lista, 0) < i:
        return
    if c == i:
        lista.e = el
    else:
        return subst(lista.urm, i, c + 1, el)

'''
Modelul matematic:
                        adevarat, elem = lista.e
exista(elem, lista) =   fals, lista e vida
                        exista(elem, lista.urm), elem != lista.e
'''

def exista(elem, lista):
    if lista == None:
        return False
    if elem == lista.e:
        return True
    return exista(elem, lista.urm)

'''
Modelul matematic:
                            {}, lista1 e vida
diferenta(lista1, lista2) = printeaza elementul daca nu se afla in lista2
                            diferenta(lista1.urm, aux.prim, aux), altfel
'''

def diferenta(lista1, lista2, aux):
    if lista1 == None:
        return
    if exista(lista1.e, lista2) == False:
        print(lista1.e)
    return diferenta(lista1.urm, aux.prim, aux)

'''
program pentru test
'''
        
def main():
    list = creareLista()
    print("Test:")
    tipar(list)
    print("Ex 3a:")
    print("Daca nu e dat i bun:")
    subst(list.prim, 10, 0, 3)
    tipar(list)
    print("Pentru un i bun:")
    subst(list.prim, 2, 0, 5)
    tipar(list)
    print("Ex 3b:")
    list2 = creareLista()
    diferenta(list.prim, list2.prim, list2)
    
main() 
    
    
    
    
    
