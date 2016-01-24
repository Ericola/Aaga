package algo.part2Tree;

import java.util.ArrayList;
import java.util.Random;

public class Abub_generator {
	public ArrayList<Double> nbTree; // liste contenant le nombre d'arbres possibles pour chaque taille
	public static int cpt = 0;
	public static boolean DEBUG = false;

	public Abub_generator(){
		this.nbTree = new ArrayList<>();
		this.nbTree.add(0.0);
		this.nbTree.add(1.0);
	}

	/**
	 * Remplit le tableau nbTree de 1 jusqu'a nb
	 * @param nb
	 */
	public void fillNb(int nb){
		for(int i = 2; i < nb; i++){
			double x = 0;
			x+= nbTree.get(i-1);
			for(int k = 1; k < i ; k++){
				x += nbTree.get(k)* nbTree.get(i - 1 - k);
			}
			nbTree.add(x);
		}
	}

	/**
	 * Genere un arbre unaire-binaire de numero tmp de taille n
	 * Si tmp != -1 alors on genere avec un numero aleatoire de taille n
	 * @param n
	 * @param tmp
	 * @return
	 */
	public Abub generate(int n, int tmp){
		if(n == 1){
			cpt++;
			Abub a = new Abub(cpt, null, null);
			return a;
		}

		int val;
		if(tmp == -1){
			Random r  = new Random();
			val = r.nextInt(nbTree.get(n).intValue());
			
			if(DEBUG)
			System.out.println("Valeur Tire :" + val);
		}
		else{
			val = tmp;
		}
		// On teste si val <= An
		if(val <= nbTree.get(n-1)){
			// noeud unaire;
			
			if(DEBUG)
			System.out.println(n);
				
			cpt++;
			Abub a = new Abub(cpt, generate(n-1, val), null);
			a.getGauche().setParent(a);
			return a;
		}
		// noeud binaire
		double x = nbTree.get(n-1);
		int borneInf = 1;
		int borneSup = 1;
		int numFilsDroit = 1;
		int numFilsGauche = 1;
		for(int k = 1; k < n - 1; k++){
			x = x + nbTree.get(k)*nbTree.get(n-1-k);
			if(val <= x){
				borneInf = k;
				borneSup = n-1-k;
				
				val = val-((int)x - (int)(nbTree.get(k)*nbTree.get(n-1-k))) ;
				
				numFilsGauche = ( (val-1) / nbTree.get(borneSup).intValue()) + 1;
				
				numFilsDroit = ((val-1) % (borneSup)) + 1;
				
				if(DEBUG){
				System.out.println("Borne inf " + borneInf);
				System.out.println("Borne sup " + borneSup);
				System.out.println("val " + val);
				System.out.println("numFilsGauche " + numFilsGauche);
				System.out.println("numFilsDroit " + numFilsDroit);
				}
				break;
			}
		}
		if(borneInf == 2){
			numFilsGauche = 1;
		}
		if(borneSup == 2){
			numFilsDroit = 1;
		}
		cpt++;
		Abub a =  new Abub(cpt, generate(borneInf, numFilsGauche), generate(borneSup, numFilsDroit));
		a.getGauche().setParent(a);
		a.getDroit().setParent(a);
		return a;

	}

	/**
	 * Algorithme naiveMinMax sur les arbres. Renvoie un tableau d'arbre contenant en premiere case 
	 * le minimum et en deuximeme case le maximum des arbres du tableau
	 * @param abub
	 * @return
	 */
	public static Abub[] naiveMinMax(Abub[] abub){
		Abub tab[] = new Abub[2];
		Abub min = abub[0];
		Abub max = abub[0];

		for(Abub a : abub){
			if(a.compareTo(min) == -1)
				min = a;
			if(a.compareTo(max) == 1)
				max = a;
		}

		tab[0] = min;
		tab[1] = max;

		return tab;
	}

	/**
	  * Algorithme optiMinMax sur les arbres. Renvoie un tableau d'arbre contenant en premiere case 
	 * le minimum et en deuximeme case le maximum des arbres du tableau
	 * @param abub
	 * @return
	 */
	public static Abub[] optiMinMax(Abub[] abub){
		Abub tab[] = new Abub[2];
		Abub min = abub[abub.length - 1];
		Abub max = abub[abub.length - 1];

		for(int i=0;i<abub.length - 1;i+=2){
			if(abub[i].compareTo(abub[i+1]) == -1){
				if(abub[i].compareTo(min) == -1){
					min = abub[i];
				}
				if(abub[i+1].compareTo(max) == 1) {
					max = abub[i+1];
				}	
			}
			else{
				if(abub[i+1].compareTo(min) == -1){
					min = abub[i+1];
				}
				if(abub[i].compareTo(max) == 1) {
					max = abub[i];
				}	   
			}
		}

		tab[0] = min;
		tab[1] = min;
		return tab;
	}
	
	/**
	 * Genere un tableau d'arbres unaire binaire. Les arbres sont de taille sizeTree et le nombre 
	 * d'arbres générés est de taille sizeArray
	 * @param sizeArray
	 * @param sizeTree
	 * @return
	 */
	public static Abub[] generateRandomArrayTree(int sizeArray, int sizeTree){
		Abub tab[] = new Abub[sizeArray];
		Abub_generator a = new Abub_generator();
		a.fillNb(100);
		for(int i = 0; i < sizeArray; i++){
			tab[i] = a.generate(sizeTree, -1);
		}

		return tab;
	}

	public ArrayList<Double> getNbTree() {
		return nbTree;
	}

	public void setNbTree(ArrayList<Double> nbTree) {
		this.nbTree = nbTree;
	}
}
