package algo.part2Tree;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class TestMinMax {

	public static void main(String[] args) throws IOException{
		String Filename = "Courbe1.txt";
		FileWriter f = new FileWriter(Filename, false);
        f.close();
		float test = 0L;
		float tab[];
		MinMax m = new MinMax();
		m.init();

		for(int j = 1;j<120000002;j+=20000000) {
			
			long duration = 0L;
			long duration2 = 0L;
			for(int k = 0; k < 10; k++){
				tab = new float[j];
				Random r = new Random();
				r.setSeed(System.currentTimeMillis());
				for(int i = 0; i < j; i++){
					tab[i] = test = r.nextFloat();;
				}
				m.init();
				long startTime = System.nanoTime();
				
				m.naive(tab);
				duration+= System.nanoTime() - startTime;
				m.init();
				startTime = System.nanoTime();
				m.opti(tab);
				duration2+= System.nanoTime() - startTime;
			}
			try {
				FileWriter fw = new FileWriter( Filename , true );
				fw.write( j + " " + duration/10000 + " "
						+ duration2/10000 + "\n" );
				fw.close();

			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
