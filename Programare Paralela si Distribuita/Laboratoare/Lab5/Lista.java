public class Lista {
    Nod head;

    public Lista() {
        Nod min = new Nod(-1, Integer.MIN_VALUE);
        Nod max = new Nod(-1, Integer.MAX_VALUE);
        min.nextNode = max;
        head = min;
    }

    public void insert(int coef, int grad){
        Nod nodNou = new Nod(coef, grad);

        Nod prec, curent;
        prec = head;
        prec.lock();
        curent = prec.nextNode;
        curent.lock();
        try{
            while(curent.grad < grad){
                prec.unlock();
                prec = curent;
                curent = curent.nextNode;
                curent.lock();
            }
            if(curent.grad == grad){ //daca exista un nod cu acest grad, ii updatam coeficientul
                curent.coeficient+=coef;
                if(curent.coeficient == 0){ //daca coeficientul devine 0, il stergem
                    this.remove(curent);
                }
            } else { //il adaugam listei
                nodNou.nextNode = curent;
                prec.nextNode = nodNou;
            }
        } finally {
            curent.unlock();
            prec.unlock();
        }
    }

    public void remove(Nod nod){
        int grad = nod.getGrad();
        Nod prec, curent;
        prec = head;
        prec.lock();
        curent = prec.nextNode;
        curent.lock();
        try{
            while(curent.grad < grad){
                prec.unlock();
                prec = curent;
                curent = curent.nextNode;
                curent.lock();
            }
            if(curent.grad == grad){
                prec.nextNode = curent.nextNode;
            }
        } finally {
            curent.unlock();
            prec.unlock();
        }
    }
}
