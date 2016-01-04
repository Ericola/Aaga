package algo;

import java.util.ArrayList;
import java.util.Random;

public class Abub_generator {
	public ArrayList<Double> nbTree;
	public static int cpt = 0;


	public Abub_generator(){
		this.nbTree = new ArrayList<>();
		this.nbTree.add(0.0);
		this.nbTree.add(1.0);
	}

	public void fillNb(int nb){
		for(int i = 2; i < nb; i++){
			double x = 0;
			x+= nbTree.get(i-1);
			for(int k = 1; k < i ; k++){
				x += nbTree.get(k)* nbTree.get(i - 1 - k);
			}
			nbTree.add(x);
			//System.out.println("Arbre de taille " + i + " : " + x);
		}
	}

	public Abub generate(int n, int tmp){
		if(n == 1){
			cpt++;
			Abub a = new Abub(cpt, null, null);
			return a;
		}
		int val;
		System.out.println("Taille : " + n + " tmp : " + tmp);
		if(tmp == -1){
			Random r  = new Random();
			val = r.nextInt(nbTree.get(n).intValue());
			System.out.println("Valeur Tire :" + val);
		}
		else{
			val = tmp;
		}
		// On teste si val <= An
		if(val <= nbTree.get(n-1)){
			// noeud unaire;
			cpt++;
			Abub a = new Abub(cpt, generate(n-1, val), null);
			a.getGauche().setParent(a);
			return a;
		}
		// noeud binaire
		double x = nbTree.get(n-1);
		int borneInf = 0;
		int borneSup = 0;
		int numFilsDroit = 0;
		int numFilsGauche = 0;
		for(int k = 1; k < n - 1; k++){
			x = x + nbTree.get(k)*nbTree.get(n-1-k);
			if(val <= x){
				borneInf = k;
				borneSup = n-1-k;
				System.out.println("Borne inf " + borneInf);
				System.out.println("Borne sup " + borneSup);
				val = val-((int)x - (int)(nbTree.get(k)*nbTree.get(n-1-k))) ;
				System.out.println("val " + val);
				numFilsGauche = ( (val-1) / nbTree.get(borneSup).intValue()) + 1;
				System.out.println("numFilsGauche " + numFilsGauche);
				numFilsDroit = ((val-1) % (borneSup)) + 1;
				System.out.println("numFilsDroit " + numFilsDroit);
				break;
			}
		}
		cpt++;
		Abub a =  new Abub(cpt, generate(borneInf, numFilsGauche), generate(borneSup, numFilsDroit));
		a.getGauche().setParent(a);
		a.getDroit().setParent(a);
		return a;

	}

	public ArrayList<Double> getNbTree() {
		return nbTree;
	}

	public void setNbTree(ArrayList<Double> nbTree) {
		this.nbTree = nbTree;
	}
}
