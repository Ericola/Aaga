package algo;

public class Main {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		for(int i =0; i<1000000000;i++){
			float[] tab = {1,2,3};
			MinMax m = new MinMax();
			m.init();
			m.naive(tab);
		}

	}
}
