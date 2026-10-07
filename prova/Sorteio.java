import java.util.Scanner;

class Participante{
	String nome;
	Participante prox;

	public Participante(String nome){
		this.nome = nome;
		prox = null;
	}
}

class Fila{
	Participante primeiro, ultimo;

	public Fila(){
		primeiro = null;
		ultimo = null;
	}

	void inserir(String nome){
		Participante p = new Participante(nome);
		if(primeiro == null){
			primeiro = p;
			ultimo = p;
		}
		else{
			ultimo.prox = p;
			ultimo = p;
		}
	}

	Participante remover(){
		Participante tmp = primeiro;
		primeiro = primeiro.prox;

		if(primeiro == null){
			ultimo = null;
		}

		return tmp;
	}

	void mostrar(){
		for(Participante i = primeiro; i != null; i = i.prox){
			System.out.print(i.nome + " ");
		}
	}

	int qtd(){
		int cont = 0;
		for(Participante i = primeiro; i != null; i = i.prox){
			cont++;
		}
		return cont;
	}
}

public class Sorteio{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);

		while(sc.hasNextInt()){

			int k = sc.nextInt();
			sc.nextLine();

			String linha = sc.nextLine();
			Scanner nomes = new Scanner(linha);

			Fila fila = new Fila();

			while(nomes.hasNext()){
				fila.inserir(nomes.next());
			}

			boolean rodada = false;

			while(fila.qtd() >= k){

				for(int i = 0; i < k - 1; i++){
					Participante p = fila.remover();
					fila.inserir(p.nome); 
				}
				fila.remover();
				fila.mostrar();
				System.out.println();

				rodada = true;
			}

			if(rodada == false){
				fila.mostrar();
			}

			nomes.close();
		}

		sc.close();		

	}
}
