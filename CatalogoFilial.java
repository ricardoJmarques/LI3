
/**
 * Write a description of class CatalogoFiliais here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

//TreeMap<mes, TreeMap<cliente,TreeSet<Venda>>>;
//TreeMap<cliente, TreeMap<mes, TreeSet<Venda>>>;

import java.util.*;
import java.io.Serializable;

public class CatalogoFilial implements Serializable
{

	private TreeMap<Integer,TreeMap<String,TreeSet<Venda>>> catFilialMes;
	private TreeMap<String,TreeMap<Integer,TreeSet<Venda>>> catFilialCliente;

	public CatalogoFilial (){

		catFilialMes = new TreeMap<Integer,TreeMap<String,TreeSet<Venda>>>();
		catFilialCliente = new TreeMap<String,TreeMap<Integer,TreeSet<Venda>>>();

	}

	public void adicionaVenda (Venda v){

		TreeMap<String,TreeSet<Venda>> auxmapM;
		TreeMap<Integer,TreeSet<Venda>> auxmapC;
		TreeSet<Venda> auxset;

		if( catFilialMes.containsKey(v.getMes()) == false ){

			auxmapM = new TreeMap<String,TreeSet<Venda>>();
			auxset = new TreeSet<Venda>(new ComparatorVendaCliente());
			
			auxset.add(v.clone());
			auxmapM.put(v.getCodigoCliente() , auxset);
			catFilialMes.put(v.getMes() , auxmapM);
		
		}

		else{

			if( catFilialMes.get(v.getMes()).containsKey(v.getCodigoCliente()) == false  ){
				auxset = new TreeSet<Venda>(new ComparatorVendaCliente());

				auxset.add(v.clone());
				catFilialMes.get(v.getMes()).put(v.getCodigoCliente() , auxset);
			}

			else {

				catFilialMes.get(v.getMes()).get(v.getCodigoCliente()).add(v.clone());

			}
		}

		if( catFilialCliente.containsKey(v.getCodigoCliente()) == false){

			auxmapC = new TreeMap<Integer,TreeSet<Venda>>();
			auxset = new TreeSet<Venda>(new ComparatorVendaCliente());
			
			auxset.add(v.clone());
			auxmapC.put(v.getMes() , auxset);
			catFilialCliente.put(v.getCodigoCliente() , auxmapC);
		}

			else {

				if( catFilialCliente.get(v.getCodigoCliente()).containsKey(v.getMes()) == false ){
					auxset = new TreeSet<Venda>(new ComparatorVendaCliente());

					auxset.add(v.clone());
					catFilialCliente.get(v.getCodigoCliente()).put(v.getMes() , auxset);
				}

				else {

					catFilialCliente.get(v.getCodigoCliente()).get(v.getMes()).add(v.clone());

				}

			}
			
	}

	//Query 2
	public int totalVendasMes (int mes , TreeSet<String> tree){
		int ret;
		Set<String> keys = new TreeSet<String>();
		
		ret = 0; //numero global de vendas 
		keys = catFilialMes.get(mes).keySet();

		for(String s : keys){
			ret += catFilialMes.get(mes).get(s).size();
			tree.add(s);
		}

		return ret;

	}

	//Query 3
	public TreeSet<Venda> totalComprasCliente (int mes, String cliente ){

		return catFilialMes.get(mes).get(cliente);

	}

	//Query 4
	public double[] vezesProdutoComprado (int mes, String produto, TreeSet<String> clientes){
		double[] ret = new double[2];
		ret[0] = 0.0; //quantas vezes foi comprado
		ret[1] = 0.0; //total faturado

		TreeMap<String,TreeSet<Venda>> tree = catFilialMes.get(mes);

		for(Map.Entry<String,TreeSet<Venda>> entry : tree.entrySet()){
			for(Venda v : entry.getValue()){
				if(v.getCodigoProduto().equals(produto)){
					ret[0] += 1.0;
					ret[1] += (v.getPreco() * v.getUnidadesCompradas());
					clientes.add(entry.getKey());
				}
			}
		}

		return ret;
	}

	/*public int getTamanhoCatFilialMes () {
		int ret = 0;
		int j;

		for(j=1; j<=12; j++){
			for(Map.Entry<String,TreerSet<Venda>> entry : catFilialMes.get(j)){
				ret+=entry.getValue().size;
			}
		}

		return ret;
	}*/
	//JP1982 343.2 168 N T1805 10 2
	/*public int getTamanhoCatFilialMes () {
		return catFilialMes.get(10).get("T1805").first().getUnidadesCompradas();
	}
	

	public int getTamanhoCatFilialCliente () {
		return catFilialCliente.get("T1805").get(10).first().getUnidadesCompradas();
	}*/
	
}
