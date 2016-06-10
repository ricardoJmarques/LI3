/**
 * Write a description of class Produtos here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.util.TreeSet;
import java.util.TreeMap;
import java.lang.String;
import java.util.ArrayList;
import java.util.Map;
import static java.lang.System.*;
import java.io.Serializable;

public class Produtos implements Serializable
{
    private static TreeMap<String,TreeSet<String>> catProds;

    public Produtos () {
        catProds = new TreeMap<String,TreeSet<String>>();
    }

    public Produtos (ArrayList<String> linhas ) {

        catProds = new TreeMap<String,TreeSet<String>>();

        //TreeSet<String> aux = new TreeSet<String>();

        char c = 'A';
        int i = 0;
        
        for (i=0; i<26; i++){ //cria 26 treesets 
            catProds.put(Character.toString(c) , new TreeSet<String>());
            c++;
        }
        /*
        for(String s : linhas){
            
            for(Map.Entry<String,TreeSet<String>> entry : catProds.entrySet()){ //lento ?? o entry set vai buscar todos os elementos do map, keySet()??
                //System.out.println(entry.getKey()); 
                if(entry.getKey().equals(s.substring(0, 1))){
                    aux = entry.getValue();
                    aux.add(s);

                    catProds.put(s.substring(0, 1) , aux);
                    break;

                }
            }
           
        }
        */
        for(String s : linhas){
            catProds.get(s.substring(0, 1)).add(s);
        }

    }

    public TreeMap<String,TreeSet<String>> getCatProds (){ //nao preciso clone??
        return catProds;
    }
    
    public static boolean existeProduto (String prod){
        //System.out.println("Produtos.prod = " + prod);
        return catProds.get(prod.substring(0, 1)).contains(prod);
    }
}
