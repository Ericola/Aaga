package algo.part2Tree;

public class MinMax {

	private float min;
	private float max;

	
	public float getMin() {
		return min;
	}

	public void setMin(float min) {
		this.min = min;
	}

	public float getMax() {
		return max;
	}

	public void setMax(float max) {
		this.max = max;
	}
	
	public void init(){
		max = Float.MAX_VALUE;
		min = Float.MIN_VALUE;
	}

	public void naive(float[] tab) {
		min = max = tab[0];
		for(int i = 1; i<tab.length;i++){
			if(tab[i]<min){
				min = tab[i];
			}
			if(tab[i]>max){
				max = tab[i];
			}
		}
	}
	
	public static boolean contains(float[] tab, float value){
		for(int i = 0; i < tab.length; i++)
			if(tab[i] == value)
				return true;
		return false;
						
	}
	
	public void opti(float[] tab){
		min = max = tab[tab.length - 1];
		for(int i=0;i<tab.length - 1;i +=2){
			if(tab[i] < tab[i+1]){
				if(tab[i]<min) min = tab[i];
				if(tab[i+1]>max) max = tab[i+1];
			}
			else {
				if(tab[i+1]<min) min = tab[i+1];
				if(tab[i]>max) max = tab[i];
			}
		}
	}

}
