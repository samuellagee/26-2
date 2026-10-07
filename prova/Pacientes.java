import java.util.Scanner;

class Paciente{
	Paciente prox;
	String nome;
	int pendencia;

	public Paciente(String nome, int pendencia){
		this.nome = nome;
		this.pendencia = pendencia;
		prox = null;
	}
}

class Fila{
	Paciente primeiro;
	Paciente ultimo;

	public Fila(){
		primeiro = null;
		ultimo = null;
	}

	void inserirFim(String nome, int pendencia){
		Paciente c = new Paciente(nome, pendencia);
		if(primeiro == null){
			primeiro = c;
			ultimo = c;
		}
		else{
			ultimo.prox = c;
			ultimo = c;
		}
	}

	void remover(){
		if(primeiro == null) System.out.println("Fila vazia");

		Paciente tmp = primeiro;
		primeiro = primeiro.prox;
		if(primeiro == null){
			ultimo = null;
		}

		tmp.pendencia--;

		System.out.println("Atendido: " + tmp.nome);
		if(tmp.pendencia > 0){
			inserirFim(tmp.nome, tmp.pendencia);	
		}
	}

	void mostrar(){
		for(Paciente i = primeiro; i != null; i = i.prox){
			System.out.println(i.nome + " " + i.pendencia);
		}
	}
}

public class Pacientes{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		Fila fila = new Fila();

		String comando;

		while(sc.hasNext()){
			comando = sc.next();

			if(comando.compareTo("I") == 0){
				String nome = sc.next();
				int pendencia = sc.nextInt();

				fila.inserirFim(nome, pendencia);
			}
			else if(comando.compareTo("R") == 0){
				fila.remover();
			}
		}
		sc.close();
	}
}
