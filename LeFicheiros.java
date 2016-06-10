
/**
 * Escreva a descrição da classe LeFicheiros aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.System.out;

public class LeFicheiros
{
    public static ArrayList<String> LeLinhas(String ficheiro) {
        ArrayList<String> linhas = new ArrayList<>();
        BufferedReader inStream = null;
        String linha = null;
        try {   
            inStream = new BufferedReader(new FileReader(ficheiro));
            while( (linha = inStream.readLine()) != null ){
                linhas.add(linha);
            }
        }
        catch(IOException e){
            out.println(e.getMessage());
            return null;
        }
        return linhas;
    }
    
}
