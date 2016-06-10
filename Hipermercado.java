
/**
 * Escreva a descrição da classe Hipermercado aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
import java.util.ArrayList;
import java.util.HashSet;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Map;
import java.util.Comparator;

public class Hipermercado
{

    public static void main (String[] args){
        
        /** Testes à classe vendas ** /
         * 
         */
        
        String fich = "ficheiros/Vendas_1M.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura = " + Crono.print());
        Crono.start();
        ArrayList<Venda>catVendas = Venda.parseAllLinhas(linhas);
        Crono.stop();
        System.out.println("Tempo Parser = " + Crono.print());
        System.out.println("Vendas Filial 1: " + Venda.comprasPorFilial(catVendas, 1));
        System.out.println("Vendas Filial 2: " + Venda.comprasPorFilial(catVendas, 2));
        System.out.println("Vendas Filial 3: " + Venda.comprasPorFilial(catVendas, 3));
        Crono.start();
        System.out.println("Vendas de valor 0: " + Venda.vendasZero(catVendas));
        Crono.stop();
        System.out.println("Tempo1 Vendas 0 = " + Crono.print());
        Crono.start();
        long totalZeros = catVendas.stream()
                                 .filter(v -> v.getPreco() == 0.0)
                                 .count();
                                 //.peek(v -> System.out.println(v)); // apenas para inspecionar
        System.out.println("Total de vendas de Preco 0.0 = " + totalZeros);
        Crono.stop();
        System.out.println("Tempo2 Vendas 0 = " + Crono.print());
        char c = 'A';
        int i = 0;
        for (i=0; i<26; i++){
            System.out.println("Produtos Começados por " + c + " : " + Venda.produtosComecados(catVendas, c));
            c++;
        }
        for (i=1; i<4; i++){
            //TreeSet<Venda> set = Venda.clientesCompraramFilial(catVendas, i);
            HashSet<String> set = Venda.clientesCompraramFilial(catVendas, i);
            System.out.println("Numero de cliente que compraram na filial " + i + " : " + set.size());
        }
        
        catVendas.sort(Comparator.comparing(Venda::getUnidadesCompradas)
                                 .reversed()
                                 .thenComparing(Comparator.comparing(Venda::getCodigoCliente))
                                 .thenComparing(Comparator.comparing(Venda::getCodigoProduto)));
        
        for(Venda vnd : catVendas)//.subset(Venda A, Venda B));
            System.out.println(vnd);

       
        /** Testes à classe produtos ** /
         * 
         */
        /*
        String fich = "ficheiros/Produtos.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura Produtos = " + Crono.print());
        System.out.println("Numero de Produtos = " + linhas.size());

        Produtos p;
        Crono.start();
        p = new Produtos(linhas);
        Crono.stop();
        System.out.println("Tempo Armazenamento Produtos = " + Crono.print());

        TreeMap<String,TreeSet<String>> aux;
        aux = p.getCatProds();
        //imprime todos os produros 
        */
        /*
        for(Map.Entry<String,TreeSet<String>> entry : aux.entrySet()){ //lento ?? o entry set vai buscar todos os elementos do map, keySet()??
                for(String str : entry.getValue()){
                    System.out.println(str);
                }
        }
        */
        /*
        String teste1 = "AF1184"; //existe
        String teste2 = "JC1996"; //nao exite;

        if(p.existeProduto(teste1) == true)
            System.out.println("AF1184 exite");

        if(p.existeProduto(teste2) == false)
            System.out.println("JC1996 nao exite");
        */
       
       
        /** Testes à classe clientes ** /
         * 
         */
        /*
        String fich = "ficheiros/Clientes.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura Produtos = " + Crono.print());
        System.out.println("Numero de Produtos = " + linhas.size());

        Clientes c;
        Crono.start();
        c = new Clientes(linhas);
        Crono.stop();
        System.out.println("Tempo Armazenamento dos Clientes = " + Crono.print());

        TreeMap<String,TreeSet<String>> aux;
        aux = c.getCatCli();
        //imprime todos os produros 
        /*
        for(Map.Entry<String,TreeSet<String>> entry : aux.entrySet()){ //lento ?? o entry set vai buscar todos os elementos do map, keySet()??
                for(String str : entry.getValue()){
                    System.out.println(str);
                }
        }
        */
        /*
        String teste1 = "B3304"; //existe
        String teste2 = "R2367"; //nao exite;

        if(c.existeCliente(teste1))
            System.out.println(teste1 + " exite");

        if(!c.existeCliente(teste2))
            System.out.println(teste2 + " nao exite");
        */
    }
}
