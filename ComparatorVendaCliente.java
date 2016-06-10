
/**
 * Write a description of class ComparatorImovel here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.util.Comparator;

public class ComparatorVendaCliente implements Comparator<Venda>
{
    public int compare(Venda a, Venda b){
        
        if (a.getCodigoProduto().equals(b.getCodigoProduto())){
            if(a.getUnidadesCompradas() == b.getUnidadesCompradas()){
                if(a.getPreco() == b.getPreco()){
                    if(a.getTipoCompra().equals(b.getTipoCompra())){
                        return 0;
                    }

                    else return a.getTipoCompra().compareTo(b.getTipoCompra());
                }

                    

                else{
                    if(a.getPreco() > a.getPreco())
                        return 1;
                    return -1;
                }
            }
            else{
                
                if(a.getUnidadesCompradas() > b.getUnidadesCompradas())
                    return 1;
                return -1;
            }

        }

        else return a.getCodigoProduto().compareTo(b.getCodigoProduto());

    }
}


