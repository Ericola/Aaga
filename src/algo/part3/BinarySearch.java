package algo.part3;

public class BinarySearch {
	
	public static int naif(float[] tab, float x){
		int d = 0;
		int f = tab.length;
		int m;
		while(d<f) {
			m = (d+f)/2;
			if(tab[m] < x){
				d = m+1;
			}
			else {
				f = m;
			}
		}
		return f;
	}
	
	public static int binaryBiasedSearch(float[] tab, float x) {
		int d = 0;
		int f = tab.length;
		int m;
		while(d<f) {
			m = (3*d+f)/4;
			if(tab[m] < x){
				d = m+1;
			}
			else {
				f = m;
			}
		}
		return f;
	}
	
	public static int skewSearch(float[] tab, float x){
		int d = 0;
		int f = tab.length;
		int m1, m2;
		while (d < f){
		   m1 = (3*d+f)/4;
		   if (tab[m1] > x)
		      f = m1;
		   else {
		      m2 = (d+f)/2;
		      if (tab[m2] > x){
		         f = m2;
		         d = m1+1;
		      }
		      else d = m2+1;
		   }
		}
		return f;
	}
	
	

}
