package algo.part4;

public class Main {

	public static void main(String[] args) {
		float[] tab = {-1,9,-3,12,-5,4};
		System.out.println("naif "+TabMaxSum.naif(tab));
		System.out.println("opti "+TabMaxSum.opti(tab,0,tab.length-1));
	}

}
