package algo;

public class TestAbubGenerator {

	public static void main(String[] args) {
		
		Abub_generator a = new Abub_generator();
		a.fillNb(100);
		Abub test = a.generate(25, a.nbTree.get(25).intValue() - 4);
		Abub test1 = a.generate(25, a.nbTree.get(25).intValue() - 4);
		System.out.println("Comparaison resultat " + test.compareTo(test1) + "");
	}
}
