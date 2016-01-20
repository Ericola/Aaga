package algo.part4;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

import algo.part2Tree.Abub_generator;

public class Main {

	public static void main(String[] args) {
		
		String Filename = "CourbeTMS.txt";
	
		FileWriter f;
		Random r = new Random();
		int[] tab;
		try {
			f = new FileWriter( Filename , false );
			f.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	
		for(int i = 1; i < 1000000; i+=50000){
			tab = new int[i];
			for(int j =0;j<i;j++){
				tab[j] = r.nextInt(100)-50;
			}
			long startTime = System.nanoTime();
			TabMaxSum.naif(tab);
			long duration = System.nanoTime() - startTime;
			startTime = System.nanoTime();
			TabMaxSum.opti(tab, 0, tab.length-1);
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
		
		//int[] tab = {-1,9,-3,12,-5,4};
		//System.out.println("naif "+TabMaxSum.naif(tab));
		//System.out.println("opti "+TabMaxSum.opti(tab,0,tab.length-1));
	}

}
