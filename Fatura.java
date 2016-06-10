
/**
 * Write a description of class Fatura here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Fatura
{
    private int unidadesVendidas;
    private double totalFaturado;
    private int totalCompras;


    public Fatura () {
        unidadesVendidas = 0;
        totalFaturado = 0.0;
        totalCompras = 0;
    }

    public Fatura (Venda v){
        unidadesVendidas = 0;
        totalFaturado = 0.0;
        totalCompras = 0;

        unidadesVendidas += v.getUnidadesCompradas();
        totalFaturado += v.getPreco() * v.getUnidadesCompradas();
        totalCompras++;
    }

    public void adicionaAFatura (Venda v){
        unidadesVendidas += v.getUnidadesCompradas();
        totalFaturado += v.getPreco() * v.getUnidadesCompradas();
        totalCompras++;
    }

    public int getUnidadesVendidas (){
        return unidadesVendidas;
    }
}
