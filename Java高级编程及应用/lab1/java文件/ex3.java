package chapter1;

import java.util.Scanner;

public class ex3 {
	public static void Ex3Main(String[] args) {//主类
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in); //创建一个Scanner
		System.out.println("请输入一个数字: ");
		double num = sc.nextDouble(); //输入一个数字
		if(num==0) {
			System.out.println("0\n");//如果是0,则输出0
		}else if(num<0){
			System.out.println("-1\n");//如果小于0,则输出-1
		}else {
			System.out.println("1\n");//如果大于0,则输出1
		}
	}
}
