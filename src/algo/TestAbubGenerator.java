package algo;

import java.io.FileWriter;
import java.io.IOException;

public class TestAbubGenerator {

	public static void main(String[] args) {
		String Filename = "Courbe.txt";
		//		Abub_generator a = new Abub_generator();
		//		a.fillNb(100);
		//Abub test = a.generate(10, 600);
		//test.generateVisualTree();
		//		Abub test1 = a.generate(25, 1168625510);
		//		test1.generateVisualTree();
		//		System.out.println("Comparaison resultat " + test.compareTo(test1) + "");

		FileWriter f;
		try {
			f = new FileWriter( Filename , false );
			f.close();
		} catch (IOException e) {
			e.printStackTrace();
		}


		Abub_generator a = new Abub_generator();
		for(int i = 1; i < 1000000; i+=50000){
			Abub[] tab = Abub_generator.generateRandomArrayTree(i, 25);
			long startTime = System.nanoTime();
			Abub_generator.naiveMinMax(tab);
			long duration = System.nanoTime() - startTime;
			startTime = System.nanoTime();
			Abub_generator.optiMinMax(tab);
			long duration2 = System.nanoTime() - startTime;
			try {
				FileWriter fw = new FileWriter( Filename , true );
				fw.write( i + " " + duration + " "
						+ duration2 + "\n" );
				fw.close();

			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}
}
