import java.util.Scanner;
import java.util.Random;

class Alteracao{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		Random gerador = new Random();
		gerador.setSeed(4);

		char l1 = (char)('a' + gerador.nextInt(26));
		char l2 = (char)('a' + gerador.nextInt(26));

		String frase = sc.nextLine();
		while(frase.charAt(0) != 'F' && frase.charAt(1) != 'I' && frase.charAt(2) != 'M'){
			String alterada = "";
			for(int i = 0; i < frase.length(); i++){
				if(frase.charAt(i) == l1){
					alterada = alterada + l2;
				}
				else alterada = alterada + frase.charAt(i);
			}

		System.out.println(alterada);

		frase = sc.nextLine();
		}
	}
}
