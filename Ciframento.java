import java.util.Scanner;

class Ciframento{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		String frase = sc.nextLine();

		while(frase.charAt(0) != 'F' && frase.charAt(1) != 'I' && frase.charAt(2) != 'M'){
			String cifrada = "";			

			for(int i = 0; i < frase.length(); i++){
				char c = (char)(frase.charAt(i) + 3);
				cifrada += c;
			}

			System.out.println(cifrada);
			frase = sc.nextLine();
		}
	}
}
