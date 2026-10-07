import java.util.Scanner;

class Ingresso{
	String nome;
	Ingresso prox;

	public Ingresso(String nome){
		this.nome = nome;
		prox = null;
	}
}

class Fila{
	Ingresso primeiro, ultimo;
	int n;	

	public Fila(int n){
		primeiro = null;
		ultimo = null;
		n = 0;
		this.n = n;
	}

	void inserir(String nome){
		Ingresso novo = new Ingresso(nome);
		if(primeiro == null){
			primeiro = novo;
			ultimo = novo;
		}
		else{
			ultimo.prox = novo;
			ultimo = novo;
		}
	
		n++;
	}

	void remover(){
		if(primeiro == null)System.out.println("VAZIA");
		else{
		Ingresso tmp = primeiro;
		primeiro = primeiro.prox;

		if(primeiro == null) ultimo = null;

		n--;
		}
	}

	void mostrar(){
		for(Ingresso i = primeiro; i != null; i = i.prox){
			System.out.print(i.nome + " ");
		}
	}

}
class Transporte{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		while(sc.hasNext()){
			int n = sc.nextInt();

			Fila fila = new Fila(n);
			for(int i = 0; i < n; i++){
				String l = sc.next();
				if(l.compareTo("CHEGA") == 0){
					String ing = sc.next();
					fila.inserir(ing);
				}
				if(l.compareTo("ONIBUS") == 0){
					int vagas = sc.nextInt();
					for(int j = 0; j < vagas; j++){
						fila.remover();
					}
					fila.mostrar();
				}
			}
			
		}

	}
} 
