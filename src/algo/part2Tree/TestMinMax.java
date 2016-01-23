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
		
		for(int j = 1;j<120002;j+=20000) {
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
			long duration = System.nanoTime() - startTime;
			startTime = System.nanoTime();
			m.opti(tab);
			long duration2 = System.nanoTime() - startTime;
			System.out.println(j + " " + "naive : " + duration + ", opti : "+ duration2  );
		}
	}

}
