import java.util.Scanner;
import java.util.Arrays;

public class lab2_2 {
	public static int f(String str) {
		int max = 1;
		int fast = 0;
		char fastC =str.charAt(0);
		for (int i = 1; i < str.length(); i++) {
			if(str.charAt(i)!=fastC) {
				fastC=str.charAt(i);
				if (max<i-fast) {
					max = i-fast;
				}
				fast=i;
			}
		}
		if(max<str.length()-fast) {
			max = str.length()-fast;
		}
		return max;
	}
	
	public static int f1(int n) {
			int cnt=0;
			int max=0;
			boolean flag=true;
			while(flag){
	            if((n&1)==1){
	                cnt++;
	               if(n>>1==0&&cnt>max)    
	            	   max=cnt;
	            }
	            else    
	            {
	                if(cnt>=max)
	                    max=cnt;
	                cnt=0;
	            }
	            n>>=1;
	            if(n==0)  break;
	        }
	   return max;
	}
	
	public static void main(String[] args) {
		if  (args.length==0) {
			System.out.println("input error!");
		}
		  int num  = Integer.parseInt(args[0]);
		  String bits = Integer.toBinaryString(num);
		  System.out.println(bits);
		  int num0=f(bits);
		  System.out.println(num0);
		  int num1=f1(num);
		  System.out.println(num1);
	}
}
