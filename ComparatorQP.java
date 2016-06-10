
/**
 * Write a description of class ComparatorQP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.util.Comparator;

public class ComparatorQP implements Comparator<ParQuantidadeProduto>
{
    public int compare(ParQuantidadeProduto a, ParQuantidadeProduto b){

        if(a.getQuantidade() == b.getQuantidade()){
            
            if(a.getProduto().equals(b.getQuantidade())){
                return 0;
            }

            else return a.getProduto().compareTo(b.getProduto());
        }

        else {
            
            if(a.getQuantidade() > b.getQuantidade())
                return 1;
        }

        return -1;
    }
}
