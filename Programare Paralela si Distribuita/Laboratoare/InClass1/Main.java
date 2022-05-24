public class Main {
	
	public static void main(String[] args) throws InterruptedException {
		int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		int c[] = new int[10];
		
		System.out.println("Hi from main 1! :)");
		
		int p = 4;
//		int p = Integer.parseInt(args[0]);
		
		Thread[] t = new Worker[p];
		
		int start = 0, end = 0;
		int chunk = c.length / p;
		int rest = c.length % p;
		
		// pentru masurarea timpului:
		long startTime = System.nanoTime();
		
		for (int i = 0; i < t.length; i++) {
			end = start + chunk;
			if (rest > 0) {
				end++;
				rest--;
			}
			t[i] = new Worker(i, start, end, a, b, c);	// transmiterea unui parametru necesita un timp destul de lung
			t[i].start();
			start = end;
		}
		
		System.out.println("Hi from main 2! :)");
		
		for (int i = 0; i < t.length; i++) {
			t[i].join();	// bariera de sincronizare
		}
		
//		Thread t = new Worker();
//		t.run();	nu folosim niciodata run -> run se executa in thread-ul main
//		t.start();	// apeleaza run dupa ce s-a creat un thread si il pune pe thread-ul ala
		
		long stopTime System.nanoTime();
		
//		double time = (double)(stopTime - startTime) / 1E6; 	// milisecunde
		
		for (int i = 0; i < c.length; i++) {
			System.out.println(c[i]);
		}
		
		System.out.println((double)(stopTime - startTime) / 1E6));
	}
}