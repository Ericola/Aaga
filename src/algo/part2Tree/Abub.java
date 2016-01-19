package algo.part2Tree;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Abub implements Comparable<Abub>{
	public static String FILENAME="abub.dot";
	public int id;
	public Abub parent;
	public Abub gauche;
	public Abub droit;
	
	public Abub(int id, Abub gauche, Abub droit) {
		parent = null;
		this.id = id;
		this.gauche = gauche;
		this.droit = droit;
	}

	
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Abub getParent() {
		return parent;
	}

	public void setParent(Abub parent) {
		this.parent = parent;
	}

	public Abub getGauche() {
		return gauche;
	}

	public void setGauche(Abub gauche) {
		this.gauche = gauche;
	}

	public Abub getDroit() {
		return droit;
	}

	public void setDroit(Abub droit) {
		this.droit = droit;
	}
	
	public String toString() {

		if(this.parent == null){
			if(gauche!=null && droit != null)
				return gauche.toString() + droit.toString();
			else if(gauche != null)
				return gauche.toString();
			else if(droit!=null)
				return droit.toString();
			else
				return "";
		}

		if(gauche!=null && droit != null)
			return parent.getId() + " -> " + this.getId() + "\n" + gauche.toString() + droit.toString();
		else if(gauche != null)
			return parent.getId() + " -> " + this.getId() + "\n" + gauche.toString();
		else if(droit!=null)
			return parent.getId() + " -> " + this.getId() + "\n" + droit.toString();
		else
			return parent.getId() + " -> " + this.getId() + "\n";
	}
	
	public void generateVisualTree(){
		File f = new File (FILENAME);

		try
		{
			FileWriter fw = new FileWriter (f);
			fw.append("digraph G {\n");
			fw.append("graph [ dpi = 150 ]\n"); 
			fw.append("nodesep=0.3;\n");
			fw.append("ranksep=0.2;\n");
			fw.append("margin=0.1;\n");
			fw.append("node [shape=circle];\n");
			fw.append("edge [arrowsize=0.8];\n");
			fw.write(this.toString());
			fw.write("}");
			fw.close();
		}
		catch (IOException exception)
		{
			System.out.println ("Erreur lors de l'ecriture " + exception.getMessage());
		}
	}
	
	public boolean isLeaf(){
		return gauche == null && droit == null;
	}

	public int taille(){
		
		if(this.isLeaf())
			return 1;
		
		if(gauche!= null && droit != null)
			return 1 + gauche.taille() + droit.taille();
		else if(gauche != null)
			return 1 + gauche.taille();
		else 
			return 1 + droit.taille();
	}
	/** Ordre total
	 *  A <bin B si et seulement si
	 *     taille(A.gauche) < taille(B.gauche)
	 *  ou
	 *         taille(A.gauche) = taille(B.gauche)
	 *     et (A.gauche < B.gauche ou (A.gauche = B.gauche et A.droit < B.droit)	
	 */
	@Override
	public int compareTo(Abub arg0) {
		if(this.equals(arg0))
			return 0;
		
		if(this == null)
			return -1;
		
		if(arg0 == null)
			return 1;
		
		if(this.taille() < arg0.taille()) 
			return -1;
//		else if(this.taille() == arg0.taille() && ((this.gauche.compareTo(arg0.gauche) == -1) )
//				|| (this.gauche.compareTo(arg0.gauche) == 0 && this.droit.compareTo(arg0.droit) == -1))
//			return -1;
		//taille(A.gauche) = taille(B.gauche)
		else if(this.taille() == arg0.taille()){
			if(this.gauche != null && arg0.gauche != null){
				if(this.gauche.compareTo(arg0.gauche) == -1)
					return -1;				
			}
		}	
		if(this.gauche != null && arg0.gauche != null){
			if(this.gauche.compareTo(arg0.gauche) == 0)
				if(this.droit != null && arg0.droit != null)
					if(this.droit.compareTo(arg0.droit) == -1)
						return -1;
				
		}		
		return 1;
	}
	
}
