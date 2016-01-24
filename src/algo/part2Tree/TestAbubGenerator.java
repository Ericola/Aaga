package algo.part2Tree;

import java.io.FileWriter;
import java.io.IOException;

public class TestAbubGenerator {

	public static void main(String[] args) {
		String Filename = "Courbe.txt";
		FileWriter f;
		try {
			f = new FileWriter( Filename , false );
			f.close();
		} catch (IOException e) {
			e.printStackTrace();
		}


		Abub_generator a = new Abub_generator();
		for(int i = 1; i < 1200000; i+=50000){
			Abub[] tab = Abub_generator.generateRandomArrayTree(i, 25);
			long startTime = System.nanoTime();
			Abub_generator.naiveMinMax(tab);
			long duration = System.nanoTime() - startTime;
			startTime = System.nanoTime();
			Abub_generator.optiMinMax(tab);
			long duration2 = System.nanoTime() - startTime;
			try {
				FileWriter fw = new FileWriter( Filename , true );
				fw.write( i + " " + duration/1000 + " "
						+ duration2/1000 + "\n" );
				fw.close();

			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}
}

