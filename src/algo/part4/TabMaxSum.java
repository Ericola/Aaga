package algo.part4;

public class TabMaxSum {


	public static int naif(int[] tab){
		int max = Integer.MIN_VALUE;
		int acc;
		for(int i =0;i<tab.length;i++){
			acc = tab[i];
			if(acc > max){
				max = acc;
			}
			for(int j=i+1;j<tab.length;j++){
				acc += tab[j];
				if(acc > max){
					max = acc;
				}
			}
		}
		return max;
	}

	public static int optiCheval(int[] tab, int g, int d){
		int max = Integer.MIN_VALUE;
		int acc = 0;
		for(int i=(int) (Math.floor((g+d)/2))+1;i<=d;i++){
			acc += tab[i];
			if(acc>max){
				max = acc;
			}
		}
		acc = max;
		for(int i = (int)Math.floor((g+d)/2) ; i>= g; i--){
			acc += tab[i];
			if(acc>max){
				max = acc;
			}
		}
		return max;
	}

	public static int opti(int[] tab, int g, int d){
		if(g>d){
			return 0;
		}
		if(g==d){
			if(tab[g] <0){
				return 0;
			}
			else {
				return tab[g];
			}
		}
		int max1 = opti(tab,g,(int)Math.floor((g+d)/2));
		int max2 = opti(tab,(int)Math.floor((g+d)/2)+1,d);
		int max3 = optiCheval(tab, g, d);

		return Math.max(max3, Math.max(max1, max2));
	}
}

