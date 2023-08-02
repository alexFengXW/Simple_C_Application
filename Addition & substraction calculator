import java.util.Scanner;
 /*
  * This is a simple calculator, you only enter signs(addition and substraction only) and integers and floats. 
	  Make sure you only enter one value once, either signs or a value.\nEnter '=' to get your result:"
  */

public class calculator {
	 static String currentStr = "";
	 static String currentSign = "+";
	 static float result = 0;


	public calculator(String value) {
		if(value.equals("+")) {
			currentStr += "+";
			currentSign = "+";
		}
		else if(value.equals("-")) {
			currentStr += "-";
			currentSign = "-";
		}
		else if(value.equals("=")) {
			currentSign = "=";
		}
		else {
			if(currentSign.equals("+")) {
				result += (Float.parseFloat(value));
			}
			else if(currentSign.equals("-")) {
				result -= (Float.parseFloat(value));
			}
			currentStr = currentStr + value;
			
		}
	}
	
	public float getResult() {
		return result;
	}
	public static String printConsole() {
		if(currentSign.equals("=")) {
			return "This is your console:" + currentStr + " = " + result;
		}
		else {
		return "This is your console:" + currentStr;
		}
	}

	public static void main(String[ ] args) {
		System.out.println("This is a simple calculator, you only enter signs(addition and substraction only) and integers and floats.\n"
				+ "Make sure you only enter one value once, either signs or a value.\nEnter '=' to get your result:" ) ;
		Scanner input = new Scanner(System.in); 
		while(input.hasNextLine()) {
			String value = input.next();
			calculator caculation = new calculator(value);
			System.out.println(caculation.printConsole());
			if(value.equals("=")) break;
		}

	}
	
}
