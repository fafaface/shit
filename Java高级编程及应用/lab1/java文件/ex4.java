package chapter1;
import java.util.Scanner;
public class ex4 {
	public static void main(String[] args) {//主类
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in); //创建一个Scanner
		System.out.println("请输入2020年里, 一个月份的数字: ");
		int num = sc.nextInt(); //输入一个数字
		switch(num){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			System.out.println(num+"月有31天\n");
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			System.out.println(num+"月有30天\n");
			break;
		default:
			System.out.println(num+"月有29天\n");
			break;
		}
	}
}
