
import java.util.Scanner;
import java.util.Arrays;
public class lab2_1 {
	public static void main(String[] args) {
		if  (args.length==0) {
			System.out.println("input error!");
		}
		  double[] b = new double[args.length];
		  
		  //5.55,6.32,5.14,1.23,6.11
		  for(int j = 0; j<b.length;j++) {
		   b[j] = Double.parseDouble(args[j]);
		   System.out.print(b[j]+" ");
		  }
		  System.out.print("\n");
	      for (int i = 0; i < b.length; i++)
	          for (int j = 0; j < b.length - 1 - i; j++)
	              if (b[j + 1] < b[j]) {
	                  double temp = b[j + 1];
	                  b[j + 1] = b[j];
	                  b[j] = temp;
	              }
		  for(int j = 0; j<b.length;j++) {
			   System.out.print(b[j]+" ");
		  }
	}
}
