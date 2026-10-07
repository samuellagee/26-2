import java.util.Scanner;

class Data{
	private int ano;
	private int mes;
	private int dia;

	public Data(int ano, int mes, int dia){
		this.ano = ano;
		this.mes = mes;
		this.dia = dia;
	}

	public static Data parseData(String s){
		Scanner sc = new Scanner(s);
		sc.useDelimiter("-");
		int ano = sc.nextInt();
		int mes = sc.nextInt();
		int dia = sc.nextInt();
		sc.close();
		return new Data(ano, mes, dia);
	}

	public String format(){
		return String.format("%02d/%02d/%04d", dia, mes, ano);
	}
}

class Veiculo{
	private int id;
	private String marca;
	private String modelo;
	private int ano;
	private String categoria;
	private String[] combustivel;
	private int cilindros;
	private double cilindrada;
	private String transmissao;
	private String tracao;
	private double consumoCidade;
	private double consumoEstrada;
	private double co2;
	private boolean turbo;
	private Data dataRegistro;

	public Veiculo(int id, String marca, String modelo, int ano, String categoria,
			String[] combustivel, int cilindros, double cilindrada,
			String transmissao, String tracao,
			double consumoCidade, double consumoEstrada, double co2,
			boolean turbo, Data dataRegistro){

		this.id = id;
		this.marca = marca;
		this.modelo = modelo;
		this.ano = ano;
		this.categoria = categoria;
		this.combustivel = combustivel;
		this.cilindros = cilindros;
		this.cilindrada = cilindrada;
		this.transmissao = transmissao;
		this.tracao = tracao;
		this.consumoCidade = consumoCidade;
		this.consumoEstrada = consumoEstrada;
		this.co2 = co2;
		this.turbo = turbo;
		this.dataRegistro = dataRegistro;
	}

	public int getId(){
		return id;
	}
	public String getMarca(){
		return marca;
	}
	public String getModelo(){
		return modelo;
	}
	public int getAno(){
		return ano;
	}
	public String getCategoria(){
		return categoria;
	}
	public String[] getCombustivel(){
		return combustivel;
	}
	public int getCilindros(){
		return cilindros;
	}
	public double getCilindrada(){
		return cilindrada;
	}
	public String getTransmissao(){
		return transmissao;
	}
	public String getTracao(){
		return tracao;
	}
	public double getConsumoCidade(){
		return consumoCidade;
	}
	public double getConsumoEstrada(){
		return consumoEstrada;
	}
	public double getCo2(){
		return co2;
	}
	public boolean getTurbo(){
		return turbo;
	}
	public Data getDataRegistro(){
		return dataRegistro;
	}

	private static String[] separarCombustivel(String combustiveis){
		Scanner sc = new Scanner(combustiveis);
		sc.useDelimiter(";");

		String[] lista = new String[5];
		int i = 0;
		while(sc.hasNext()){
			lista[i++] = sc.next();
		}

		sc.close();
		return lista;
	}
	public static Veiculo parseVeiculo(String s){
		Scanner sc = new Scanner(s);
		sc.useDelimiter(",");
		sc.useLocale(java.util.Locale.US);
		int id = sc.nextInt();
		String marca = sc.next();
		String modelo = sc.next();
		int ano = sc.nextInt();
		String categoria = sc.next();
		String[] combustivel = separarCombustivel(sc.next());
		int cilindros = sc.nextInt();
		double cilindrada = sc.nextDouble();
		String transmissao = sc.next();
		String tracao = sc.next();
		double consumoCidade = sc.nextDouble();
		double consumoEstrada = sc.nextDouble();
		double co2 = sc.nextDouble();
		boolean turbo = (sc.next().charAt(0) == 't');

		Data dataRegistro = Data.parseData(sc.next());
		sc.close();
		return new Veiculo(id, marca, modelo, ano, categoria, combustivel,
				cilindros, cilindrada, transmissao, tracao,
				consumoCidade, consumoEstrada, co2, turbo, dataRegistro);
	}

	public String format(){
		String combustiveis = "";
		for(int i = 0; i < combustivel.length && combustivel[i] != null; i++){
			combustiveis += combustivel[i];
			if(i < combustivel.length - 1 && combustivel[i+1] != null){
				combustiveis += ",";
			}
		}

		return "[" + id + " ## " + marca + " ## " + modelo + " ## " + ano + " ## " + categoria
			+ " ## [" + combustiveis + "] ## " + cilindros + " ## " + cilindrada
			+ " ## " + transmissao + " ## " + tracao + " ## " + String.format("%.2f", consumoCidade)
			+ " ## " + String.format("%.2f", consumoEstrada) + " ## " + co2 + " ## " + turbo
			+ " ## " + dataRegistro.format() + "]";
	}
}
class LeitorCsv{
	public static Veiculo[] ler(String caminhoArquivo){
		int total = contarLinhas(caminhoArquivo);
		Veiculo[] veiculos = new Veiculo[total];

		try{
			Scanner sc = new Scanner(new java.io.File(caminhoArquivo));
			if(sc.hasNextLine()) sc.nextLine();
			int i = 0;
			while(sc.hasNextLine()){
				veiculos[i++] = Veiculo.parseVeiculo(sc.nextLine());
			}

			sc.close();
		}catch(Exception e){
			System.out.println("Erro ao ler arquivo");
		}

		return veiculos;
	}
	private static int contarLinhas(String caminhoArquivo){
		int total = 0;

		try{
			Scanner sc = new Scanner(new java.io.File(caminhoArquivo));
			if(sc.hasNextLine()) sc.nextLine();
			while(sc.hasNextLine()){
				sc.nextLine();
				total++;
			}

			sc.close();
		}catch(Exception e){
			System.out.println("Erro ao ler arquivo");
		}

		return total;
	}
}

class No {
	private Veiculo dado;
	private No proximo;

	public No(Veiculo dado, No proximo){
		this.dado = dado;
		this.proximo = proximo;
	}

	public Veiculo getDado(){
		return dado;
	}
	public No getProximo(){
		return proximo;
	}
}

class Pilha {
	private No topo;

	public Pilha(){
		topo = null;
	}

	public void empilhar(Veiculo veiculo){
		No novo = new No(veiculo, topo);
		topo = novo;
	}

	public Veiculo desempilhar() throws Exception {
		if(topo == null){
			throw new Exception("Erro ao remover!");
		}

		Veiculo resp = topo.getDado();
		topo = topo.getProximo();

		return resp;
	}

	public void mostrar(){
		No atual = topo;

		while(atual != null){
			System.out.println(atual.getDado().format());
			atual = atual.getProximo();
		}
	}
}

public class Veiculos12{
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);

		Veiculo[] veiculos = LeitorCsv.ler("/tmp/veiculos.csv");

		Pilha pilha = new Pilha();

		int id = sc.nextInt();
		while(id != -1){
			Veiculo v = buscar(veiculos, id);
			pilha.empilhar(v);
			id = sc.nextInt();
		}

		int qtd = sc.nextInt();

		for(int c = 0; c < qtd; c++){
			String cmd = sc.next();

			if(cmd.compareTo("I") == 0){
				int novoId = sc.nextInt();
				Veiculo v = buscar(veiculos, novoId);
				pilha.empilhar(v);

			}else if(cmd.compareTo("R") == 0){
				Veiculo removido = pilha.desempilhar();
				System.out.println("(R)" + removido.getMarca() + " " + removido.getModelo());
			}
		}

		pilha.mostrar();

		sc.close();
	}

	private static Veiculo buscar(Veiculo[] veiculos, int id){
		int i = 0;
		boolean achou = false;
		Veiculo resp = null;

		while(i < veiculos.length && achou != true){
			if(veiculos[i].getId() == id){
				resp = veiculos[i];
				achou = true;
			}
			i++;
		}

		return resp;
	}
}

