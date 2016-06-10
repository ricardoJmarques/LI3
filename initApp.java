
/**
 * Aplicação do menu em modo texto para interação do utilizador com a plataforma.
 * 
 * @author João Padrão, Rafael Alves, Ricardo Marques
 * @version 1.0
 */

import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;
import java.util.Scanner;
import java.util.TreeSet;

public class initApp
{
    private initApp() {}
    
    private static Menu menuPrincipal, menuFicheiros, menuQuerys;
    
    private static Clientes catCli;
    private static int flagCatCli; //serve para saber se os clientes ja foram carregados
    
    private static Produtos catProd;
    private static int flagCatProd; //serve para saber se os produtos ja foram carregados
    private static int flagVendas; //serve para saber se as vendas ja foram carregados
    
    private static ArrayList<CatalogoFilial> catFil;
    private static final int nFiliais = 3;

    private static CatalogoFaturacao catFact;
    /*private static Vendas catVendas;*/
    /*public static Imoobiliaria initApp();*/
    
    // Método principal
    public static void main(String[] args) {
        flagCatCli = 0;
        flagCatProd = 0;
        flagVendas = 0;
        catFil = new ArrayList<CatalogoFilial>();
        catFact = new CatalogoFaturacao();
        carregaMenu();
        int i;
        for(i=0; i<nFiliais; i++){
            catFil.add(i , new CatalogoFilial());
        }

        i = 0;
        /*carregarDados();*/
        do {
            menuPrincipal.executa();
            switch (menuPrincipal.getOpcao()) {
                case 1:
                    carregaFicheiros();
                break;
                case 2:
                    carregaQuerys();
                break;
                case 3:
                break;
            }
        } while (menuPrincipal.getOpcao()!=0);
    /*    try {
            tab.gravaObj("estado.tabemp");
            tab.log("log.txt", true);
        }
        catch (IOException e) {
            System.out.printlnln("\t\tATENÇÃO! \nErro na gravação dos dados!");
        }*/
        System.out.println("\n************ Aplicação Terminada. ************\n");     
    }
            
    private static void carregaMenu() {
        /**Opções validas para todos os utilizadores registados e não registados*/
        String[] principal = {"Carregar Ficheiros",
                              "Querys"};
                         
        /**Opções validas apenas para o caso de quando se quer fazer o registo de um utilizador*/
        String[] ficheiros = {"Carregar Ficheiro Clientes.txt",
                              "Carregar Ficheiro Produtos.txt",
                              "Carregar Ficheiro Vendas.txt"};
                            
        String[] querys = {"Query 1",
                           "Query 2",
                           "Query 3",
                           "Query 4",
                           "Query 5",
                           "Query 6",
                           "Query 7",
                           "Query 8",
                           "Query 9"};
                              
        menuPrincipal = new Menu(principal);
        menuFicheiros = new Menu(ficheiros);
        menuQuerys = new Menu(querys);
    }
    
    /* Funções do Gerais*/
    private static void carregaFicheiros() {
        menuFicheiros.executa();
        if (menuFicheiros.getOpcao() != 0) {
            switch (menuFicheiros.getOpcao()) {
                case 1:
                    carregaFicheiroClientes();
                break;
                case 2:
                    carregaFicheiroProdutos();
                break;
                case 3:
                    carregaFicheiroVendas();
                break;

            }
        }
        else{
            System.out.println("Item do Menu inexistente!");
        }
    }

    private static void carregaQuerys() {
        menuQuerys.executa();
        if (menuQuerys.getOpcao() != 0) {
            switch (menuQuerys.getOpcao()) {
                case 1:
                    q1();
                break;
                case 2:
                    q2();
                break;
                case 3:
                    q3();
                break;
                case 4:
                    q4();
                break;
                case 5:
                    q5();
                break;
                case 6:
                    q6();
                break;
                case 7:
                    q7();
                break;
                case 8:
                    q8();
                break;
                case 9:
                    q9();
                break;
            }
        }
        else{
            System.out.println("Item do Menu inexistente!");
        }
    }
    
    private static void carregaFicheiroClientes() {
        String fich = "ficheiros/Clientes.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura Clientes = " + Crono.print());
        System.out.println("Numero de Clientes = " + linhas.size());

        Crono.start();
        catCli = new Clientes(linhas);
        Crono.stop();
        System.out.println("Tempo Armazenamento dos Clientes = " + Crono.print());
        
        flagCatCli++;
        
        PressParaContinuar(); 
    }
    
    private static void carregaFicheiroProdutos() {
        String fich = "ficheiros/Produtos.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura Produtos = " + Crono.print());
        System.out.println("Numero de Produtos = " + linhas.size());

        Crono.start();
        catProd = new Produtos(linhas);
        Crono.stop();
        System.out.println("Tempo Armazenamento dos Produtos = " + Crono.print());

        flagCatProd++;

        PressParaContinuar();
    }
    
    private static void carregaFicheiroVendas() {

        if(flagCatProd == 0){
            System.out.println("A carregar Produtos...");
            carregaFicheiroProdutos();
        }

        if(flagCatCli == 0){
            System.out.println("A carregar Clientes...");
            carregaFicheiroClientes();
        }

        String fich = "ficheiros/Vendas_1M.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura Vendas = " + Crono.print());

        Crono.start();
        //System.out.println("numero de vendas validas = " + catVendas.getTamanhoCatFilialMes());
        //System.out.println("numero de vendas validas = " + catVendas.getTamanhoCatFilialCliente());
        for(String s : linhas){
            
            Venda aux = Venda.parseLinhaVenda(s);
            
            if(aux != null && Produtos.existeProduto(aux.getCodigoProduto()) && Clientes.existeCliente(aux.getCodigoCliente())){
                catFil.get(aux.getFilial()-1).adicionaVenda(aux);
                catFact.adicionaVenda(aux);
            }

            
        }
        Crono.stop();
        System.out.println("Tempo Verificação e Armazenamento das Vendas = " + Crono.print());
        //System.out.println("Numero de ficheiros faturados adicionados = " + catFact.getTamanho());
    }
        
    private static void q1(){
        ArrayList<String> produtos = new ArrayList<String>();
        produtos = catFact.produtosNuncaComprados(catProd);
        System.out.println("Numero de produtos que nunca foram comprados = " + produtos.size());
        Collections.sort(produtos);
        
        /*for(String s: produtos){
            System.out.println(s);
        
        }*/
    }

    private static void q2(){
        int mes;
        int i, res;
        TreeSet<String> tree = new TreeSet<String>();
        Scanner in = new Scanner(System.in);

        System.out.print("Insira o mes: ");
        mes = in.nextInt();
        res = 0;
        
        if(mes>=1 && mes<= 12 ){
        
            for(i=0; i<nFiliais; i++){
                res += catFil.get(i).totalVendasMes(mes , tree);
            }

            System.out.println("numero total global de vendas realizadas no mes " + mes + " : " + res);
            System.out.println("numero de clientes distintos = " + tree.size());
        }

        else {
            System.out.println("mes invalido");
        }


    }

    private static void q3(){
        int mes, i, treesize;
        double totalGastoMes , totalGastoAno, totalGastoFilial;
        TreeSet<Venda> tree;
        TreeSet<String> produtos;
        Scanner in = new Scanner(System.in);
        String cliente;

        totalGastoAno = 0.0;
        tree = new TreeSet<Venda>();

        System.out.print("Insira codigo de cliente : ");
        cliente = in.next();

        if (catCli.existeCliente(cliente)){

            System.out.println("Mes\t# Compras\t# Produtos\t# Total Gasto");
            
            for(mes=1; mes<=12; mes++){
                treesize = 0;
                System.out.print(mes + "\t");
                
                produtos = new TreeSet<String>();
                totalGastoMes = 0.0;
                
                for(i=0; i<nFiliais; i++){
                    
                    totalGastoFilial = 0.0;
                    treesize = 0;
                    
                    tree = catFil.get(i).totalComprasCliente(mes , cliente);

                    if(tree  == null){
                        treesize+= 0;
                    }

                    else{

                        for(Venda v : tree){
                            produtos.add(v.getCodigoProduto());
                            totalGastoFilial += (v.getPreco() * v.getUnidadesCompradas());
                        }

                        totalGastoMes += totalGastoFilial;
                        treesize += tree.size();

                    }
                    
                }

                totalGastoAno += totalGastoMes;
                System.out.println(treesize + "\t\t" + produtos.size() + "\t\t" + totalGastoMes );

            }

            System.out.println("Total gasto no ano: " + totalGastoAno);
        }

        else System.out.println("Codigo de cliente inexistente");


    }

    private static void q4(){
        String produto;
        int mes, i, vezesComprado;
        double totalFaturado;
        Scanner in = new Scanner(System.in);
        double[] ret = new double[2];
        TreeSet<String> clientes = new TreeSet<String>();
        
        System.out.print("Insira codigo de produto : ");
        produto = in.next();

        if (catProd.existeProduto(produto)){
            
            System.out.println("Mes\t# Vezes Comprado\t# Clientes Diferentes\t# Total Faturado");

            for(mes=1; mes<=12; mes++){
                System.out.print(mes + "\t");
                vezesComprado = 0;
                totalFaturado = 0.0;
                clientes = new TreeSet<String>();
                
                for(i=0; i<nFiliais; i++){
                    ret = catFil.get(i).vezesProdutoComprado(mes, produto, clientes);
                    vezesComprado += (int) ret[0];
                    totalFaturado += ret[1];
                }

                System.out.println(vezesComprado + "\t\t\t" + clientes.size() + "\t\t\t" + totalFaturado);
            }
        }
    }

    private static void q5(){
        String cliente;
        Scanner in = new Scanner(System.in);
        TreeSet<ParQuantidadeProduto> tree = new TreeSet<ParQuantidadeProduto>(new ComparatorQP());

        System.out.print("Insira codigo de cliente : ");
        cliente = in.next();


    }

    private static void q6(){
        System.out.println("Query 6");
    }

    private static void q7(){
        System.out.println("Query 7");
    }

    private static void q8(){
        System.out.println("Query 8");
    }

    private static void q9(){
        System.out.println("Query 9");
    }
    
    private static void PressParaContinuar() { 
        System.out.print("Pressione para continuar...");
        try {
            System.in.read();
        }  
        catch(Exception e){}  
    }
}

/*
    private static void carregaFicheiroVendas() {

        if(flagCatProd == 0){
            System.out.println("A carregar Produtos...");
            carregaFicheiroProdutos();
        }

        if(flagCatCli == 0){
            System.out.println("A carregar Clientes...");
            carregaFicheiroClientes();
        }

        String fich = "ficheiros/Vendas_1M.txt";
        Crono.start();
        ArrayList<String>linhas = LeFicheiros.LeLinhas(fich);
        Crono.stop();
        System.out.println("Tempo Leitura Vendas = " + Crono.print());

        Crono.start();
        catVendas = new CatalogoVendas(linhas);
        Crono.stop();
        System.out.println("Tempo Verificação e Armazenamento das Vendas = " + Crono.print());
        System.out.println("numero de vendas validas = " + catVendas.getTamanho());
    }
    
    
    
    private static void PressParaContinuar() { 
        System.out.print("Pressione para continuar...");
        try {
            System.in.read();
        }  
        catch(Exception e){}  
    }

*/