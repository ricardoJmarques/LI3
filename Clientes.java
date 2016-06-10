
/**
 * Write a description of class Clientes here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.util.TreeSet;
import java.util.TreeMap;
import java.lang.String;
import java.util.ArrayList;
import java.util.Map;
import java.io.Serializable;

public class Clientes implements Serializable
{
    private static TreeMap<String,TreeSet<String>> catCli;

    public Clientes () {
        catCli = new TreeMap<String,TreeSet<String>>();
    }

    public Clientes (ArrayList<String> linhas ) {

        catCli = new TreeMap<String,TreeSet<String>>();

        //TreeSet<String> aux = new TreeSet<String>();

        char c = 'A';
        int i = 0;
        
        for (i=0; i<26; i++){ //cria 26 treesets 
            catCli.put(Character.toString(c) , new TreeSet<String>());
            c++;
        }
        /*
        for(String s : linhas){
            
            for(Map.Entry<String,TreeSet<String>> entry : catCli.entrySet()){ //lento ?? o entry set vai buscar todos os elementos do map, keySet()??
                //System.out.println(entry.getKey()); 
                if(entry.getKey().equals(s.substring(0, 1))){
                    aux = entry.getValue();
                    aux.add(s);

                    catCli.put(s.substring(0, 1) , aux);
                    break;

                }
            }
           
        }
        */
        for(String s : linhas){
            catCli.get(s.substring(0, 1)).add(s);
        }

    }

    public TreeMap<String,TreeSet<String>> getCatCli (){ //nao preciso clone??
        return catCli;
    }
    
    public static boolean existeCliente (String cliente){
        //System.out.println("Clientes.cliente = " + cliente);
        return catCli.get(cliente.substring(0, 1)).contains(cliente);
    }
}
