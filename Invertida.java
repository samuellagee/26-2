import java.util.Scanner;

class Invertida{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		String p = sc.nextLine();

		while(p.charAt(0) != 'F' && p.charAt(1) != 'I' && p.charAt(2) != 'M'){
			String invertida = "";

			for(int i = p.length() - 1; i >= 0; i--){
				char c = p.charAt(i);
				invertida = invertida + c;
			}

			System.out.println(invertida);

			p = sc.nextLine();
		}
	}

}
