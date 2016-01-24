package algo.part3;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;

public class MainPart3 {

	
	/**
	 * Execute les 3 algorithmes sur des tableaux de float aléatoires de taille 1 à 1000000
	 * et ecris dans un fichier les résultats
	 * @param args
	 */
	public static void main(String[] args) {
		String Filename = "CourbePart3.txt";

		FileWriter f;
		Random r = new Random();
		float[] tab;
		try {
			f = new FileWriter( Filename , false );
			f.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		for(int i = 1; i < 1000000; i+=50000){
			System.out.println();
			tab = new float[i];
			for(int j =0;j<i;j++){
				tab[j] = r.nextFloat();
			}
			Arrays.sort(tab);
			float x = r.nextFloat();
			long startTime = System.nanoTime();
			System.out.println("naif: "+ BinarySearch.naif(tab, x));
			long duration = System.nanoTime() - startTime;
			startTime = System.nanoTime();
			System.out.println("biased: "+ BinarySearch.binaryBiasedSearch(tab, x));
			long duration2 = System.nanoTime() - startTime;
			startTime = System.nanoTime();
			System.out.println("skew: "+ BinarySearch.skewSearch(tab, x));
			long duration3 = System.nanoTime() - startTime;
			try {
				FileWriter fw = new FileWriter( Filename , true );
				fw.write( i + " " + duration + " "
						+ duration2 + " "+ duration3 +"\n" );
				fw.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
