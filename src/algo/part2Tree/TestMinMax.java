package algo.part2Tree;

import java.util.Random;

public class TestMinMax {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		float test = 0L;
		float tab[];
		MinMax m = new MinMax();
		m.init();

		for(int j = 1;j<500002;j+=50000) {
			long duration = 0L;
			long duration2 = 0L;
			for(int k = 0; k < 1; k++){
				tab = new float[j];
				Random r = new Random();
				r.setSeed(System.currentTimeMillis());
				for(int i = 0; i < j; i++){
					do{
						test = r.nextFloat();
					}while(MinMax.contains(tab, test));
					tab[i] = test;
				}
				long startTime = System.nanoTime();
				m.naive(tab);
				duration+= System.nanoTime() - startTime;
				startTime = System.nanoTime();
				m.opti(tab);
				duration2+= System.nanoTime() - startTime;
			}
			System.out.println("taille : " + j + " " + "naive (nanoseconds) : " + duration + ", opti : "+ duration2  );
		}
	}

}
