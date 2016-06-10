/**
 * Write a description of class Venda here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileReader;
import java.lang.Exception;
import java.io.IOException;
import java.lang.System.*;

import static java.lang.System.out;

import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import java.util.Comparator;

public class Venda{

    private String codigoProduto;
    private double preco;
    private int unidadesCompradas;
    private String tipoCompra;
    private String codigoCliente;
    private int mes;
    private int filial;

    public Venda (String prod, double prc, int ucmp, String tcmp, String cli, int m, int fil){
        this.codigoProduto = prod;
        this.preco = prc;
        this.unidadesCompradas = ucmp;
        this.tipoCompra = tcmp;
        this.codigoCliente = cli;
        this.mes = m;
        this.filial = fil;
    }

    public Venda (Venda v){
        this.codigoProduto = v.getCodigoProduto();
        this.preco = v.getPreco();
        this.unidadesCompradas = v.getUnidadesCompradas();
        this.tipoCompra = v.getTipoCompra();
        this.codigoCliente = v.getCodigoCliente();
        this.mes = v.getMes();
        this.filial = v.getFilial();
    }

    public String getCodigoProduto (){
        return this.codigoProduto;
    }

    public double getPreco (){
        return this.preco;
    }

    public int getUnidadesCompradas (){
        return this.unidadesCompradas;
    }

    public String getTipoCompra (){
        return this.tipoCompra;
    }

    public String getCodigoCliente (){
        return this.codigoCliente;
    }

    public int getMes (){
        return this.mes;
    }

    public int getFilial (){
        return this.filial;
    }

    public boolean equals (Object o){
        if (this == o)
            return true;
        if (o == null || o.getClass() != this.getClass())
            return false;

        Venda v = (Venda) o;

        if (v.getCodigoProduto().equals(this.codigoProduto) && v.getPreco() == this.preco && v.getUnidadesCompradas() == this.unidadesCompradas && v.getTipoCompra().equals(this.tipoCompra) && v.getCodigoCliente().equals(this.codigoCliente) && v.getMes() == this.mes && v.getFilial() == this.filial)
            return true;
        return false;
    }

    public String toString(){
        StringBuilder msg = new StringBuilder();
        msg.append("Descrição da Venda:");
        msg.append("\n\tCliente: "); 
        msg.append (codigoCliente);
        msg.append("\n\tProduto: ");
        msg.append(codigoProduto);
        msg.append("\n\tTipo de promoção: (P:promoção; N:Preço sem promoção)");
        msg.append(tipoCompra);
        msg.append("\n\tPreço unitário: ");
        msg.append(preco); 
        msg.append("\n\tQuantidade comprada: ");         
        msg.append(unidadesCompradas);
        msg.append("\n\tFilial onde foi feita a compra: ");
        msg.append(filial);
        msg.append("\n\tMês em que foi efetuada a compra: ");
        msg.append(mes);           
        return msg.toString();
    }

    protected Venda clone(){
        return new Venda(this);
    }
    
    class VendaString implements Comparator<String>{
        @Override
        public int compare(String s1, String s2) {
            return s1.compareTo(s2);
        }
    }  
    
    public static Venda parseLinhaVenda (String linha){
        /* KR1583 77.72 128 P L4891 2 1 */
        String[] campos = linha.split(" ");
        double preco;
        int qtd;
        char tipo;
        int mes;
        int filial;

        try{
            preco = Double.parseDouble(campos[1]);
        }
        catch(NullPointerException | NumberFormatException exc) {
            return null;
        }

        try{
            qtd = Integer.parseInt(campos[2]);
        }
        catch(NullPointerException | NumberFormatException exc) {
            return null;
        }

        try{
            mes = Integer.parseInt(campos[5]); /*mes>=1 && mes<=12*/
        }
        catch(NullPointerException | NumberFormatException exc) {
            return null;
        }

        try{
            filial = Integer.parseInt(campos[6]);
        }
        catch(NullPointerException | NumberFormatException exc) {
            return null;
        }

        return new Venda(campos[0],preco,qtd,campos[3],campos[4],mes,filial);
        
    }
    
    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas) {
        Set<String> set = new HashSet<String>(linhas); /*cria set para remover duplicados*/
        ArrayList<Venda> lista = new ArrayList<>();
        for(String s : set) { 
            lista.add(parseLinhaVenda(s));
        }
        out.println(linhas.size());
        out.println(lista.size());
        return lista;  
    } 
    
    public static int comprasPorFilial(ArrayList<Venda> vendas, int filial){
        int i = 0;
        for(Venda v : vendas) {
            if (v.getFilial() == filial)
              i++;
        }
        return i;
    }
    
    public static int vendasZero(ArrayList<Venda> vendas){
        int i = 0;
        for(Venda v : vendas) {
            if (v.getPreco() == 0.0)
              i++;
        }
        return i;        
    }
    
    public static int produtosComecados(ArrayList<Venda> vendas, char c){
        Set<String> set = new HashSet<>();
        int i = 0;
        for(Venda v : vendas) {
            set.add(v.getCodigoProduto());
        }
        for(String s : set){
            if (s.substring(0, 1).equals(Character.toString(c)))
            i++;
        }
        return i;        
    }
     
    public static HashSet<String> clientesCompraramFilial(ArrayList<Venda> vendas, int filial){
        HashSet<String> set = new HashSet<>();
        for(Venda v : vendas) {
            if(v.getFilial() == filial)
                set.add(v.getCodigoCliente());
        }
        return set;
    }
    
        
    public TreeSet<String> clientesCompraramFilial2(ArrayList<Venda> vendas, int filial){
        TreeSet<String> set = new TreeSet<>(new VendaString());
        for(Venda v : vendas) {
            if(v.getFilial() == filial)
                set.add(v.getCodigoCliente());
        }
        return set;
    }

}

