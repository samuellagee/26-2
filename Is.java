import java.util.Scanner;

class Is{
	//verifica se é composta so por vogais
	public static boolean vogal(String p){
		boolean resp = true;
		for(int i = 0; i < p.length(); i++){
			if(p.charAt(i) != 'a' || p.charAt(i) != 'e' || p.charAt(i) != 'i' || p.charAt(i) != 'o' || p.charAt(i) != 'u' || p.charAt(i) != 'A' || p.charAt(i) != 'E' || p.charAt(i) != 'I' || p.charAt(i) != 'O' || p.charAt(i) != 'U'){
				resp = false;
			}
		}

		return resp;
	}
	//verifica se existem vogais na string
	public static boolean consoante(String p){
		boolean resp = true; 
		for(int i = 0; i < p.length(); i++){
			if(p.charAt(i) == 'a' || p.charAt(i) == 'e' || p.charAt(i) == 'i' || p.charAt(i) == 'o' || p.charAt(i) == 'u' || p.charAt(i) == 'A' || p.charAt(i) == 'E' || p.charAt(i) == 'I' || p.charAt(i) == 'O' || p.charAt(i) == 'U'){
				resp = false;
			}
		}

		return resp;
	}

	//verifica se contem numero inteiros negativos e positivos
	public static boolean inteiro(String p){
		boolean resp = true;
		int i = 0;
		if(p.charAt(0) == '-'){
			if(p.length() == 1) resp = false;
			i = 1;
		}
		for(; i < p.length(); i++){
			if(p.charAt(i) < '0' || p.charAt(i) > '9'){
				resp = false;
			}
		}
		return resp;
	}

	//verifica se o numero é real, lendo se existem pontos ou virgulas
	public static boolean real(String p){
		boolean resp = true;
		int ponto = 0;
		int i = 0;

		if(p.length() == 0) return false;

		if(p.charAt(0) == '-'){
			if(p.length() == 1) return false;
			i = 1;
		}

		for(; i < p.length(); i++){
			char c = p.charAt(i);

			if(c == '.' || c == ','){
				ponto++;
				if(ponto > 1) resp = false; 
			} else if(c < '0' || c > '9'){ 
				resp = false; 
			}
		}

		return resp;
	}

	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		String p = sc.nextLine();
		String x1 = "";
		String x2 = "";
		String x3 = "";
		String x4 = "";
		while(!(p.length() == 3 && p.charAt(0) == 'F' && p.charAt(1) == 'I' && p.charAt(2) == 'M')){
			if(vogal(p) == true){
				x1 = "SIM";
			}else x1 = "NAO";
			if(consoante(p) == true){
				x2 = "SIM";
			}else x2 = "NAO";
			if(inteiro(p) == true){
				x3 = "SIM";
			}else x3 = "NAO";
			if(real(p) == true){
				x4 = "SIM";
			}else x4 = "NAO";
			System.out.println(x1 + " " + x2 + " " + x3 + " " + x4);
			p = sc.nextLine();
		}
	}
}
