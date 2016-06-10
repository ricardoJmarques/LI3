
/**
 * Write a description of class ParQuantidadeProduto here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ParQuantidadeProduto
{
    private int quantidade;
    private String produto;

    public ParQuantidadeProduto (Venda v){
        quantidade = v.getUnidadesCompradas();
        produto = v.getCodigoProduto();
    }

    public void adicionaQuantidade (Venda v){
        quantidade += v.getUnidadesCompradas();
    }

    public int getQuantidade (){
        return quantidade;
    }

    public String getProduto (){
        return produto;
    }
}
