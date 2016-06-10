
/**
 * Escreva a descrição da classe CatalogoFaturacao aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
import java.io.Serializable;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.Map;

public class CatalogoFaturacao implements Serializable
{
    private static TreeMap<String,TreeMap<Integer,Fatura>> catFaturacao;

    public CatalogoFaturacao () {
        catFaturacao = new TreeMap<String,TreeMap<Integer,Fatura>>();
    }

	public int getTamanho (){
		return catFaturacao.size();
	}
    
    public static void adicionaVenda(Venda v){
        String produto = v.getCodigoProduto();
        int mes = v.getMes();
        Fatura aux;

        //aux(v);
        
        TreeMap<Integer,Fatura> faturasMes;
        
        if (catFaturacao.containsKey(produto)){
            
            if(catFaturacao.get(produto).containsKey(mes)){
                
                catFaturacao.get(produto).get(mes).adicionaAFatura( v );
            }

            else{
                
                aux = new Fatura(v);
                catFaturacao.get(produto).put(mes , aux );
            }
        }
        else{

            faturasMes = new TreeMap<Integer, Fatura>();
            aux = new Fatura(v);
            faturasMes.put(mes, aux);
            catFaturacao.put(produto,faturasMes);
        }
    }

    /*
    public ArrayList<String> produtosNuncaComprados () {
        ArrayList<String> lista = new ArrayList<String>();
        int i;

        for(Map.Entry<String,TreeMap<Integer, Fatura>> entry : catFaturacao.entrySet()){

            for(i=0; i<12; i++){

                if(entry.getValue().containsKey(i)){
                    System.out.println(entry.getKey());
                    if (entry.getValue().get(i).getUnidadesVendidas() == 0){
                        lista.add(entry.getKey());
                    }
                }
            }


        }

        return lista;
    }
    */
    //query 1
    public ArrayList<String> produtosNuncaComprados (Produtos catProd) {
        ArrayList<String> lista = new ArrayList<String>();
        int i;
        char c = 'A';
        
        for (i=0; i<26; i++){

            for(String produto : catProd.getCatProds().get(Character.toString(c)) ){
                
                if(catFaturacao.containsKey(produto) == false){
                    lista.add(produto);
                }
            }
            
            c++;
        }

        return lista;
    }
                
}
