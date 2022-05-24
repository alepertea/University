import java.lang.Math;

public class Worker extends Thread {
	
	private int i, start, end;
	private int[] a, b, c;
	
	public Worker(int i, int start, int end, int[] a, int[] b, int[] c) {
		this.i = i;
		this.start = start;
		this.end = end;
		this.a = a;
		this.b = b;
		this.c = c;
	}
	
	@Override
	public void run() {	
		System.out.println("Hello from thread " + i);
		
		// Timpul pentru radical a fost putin mai lung - in jur de 60, iar pentru suma a fost intre 50-60
		for (int i = start; i < end; i++) {
//			c[i] = a[i] + b[i];
			c[i] = (int)Math.sqrt(Math.pow(a[i], 4.0) + Math.pow(b[i], 4.0));
		}
	}
}