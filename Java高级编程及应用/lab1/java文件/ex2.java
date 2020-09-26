package chapter1;
import java.util.Scanner;//导入Scanner包
// @author yuehan lian
//由于本实验内容2的目的在于练习键盘输入和运行结果输出, 因此不考虑求任意数值的倒数的情况
public class ex2 {//实验内容2, 求倒数的程序
	public static void Ex2Main(String[] args) {//主类
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in); //创建一个Scanner
		int num = sc.nextInt(); //输入分子
		int den = sc.nextInt(); //输入分母
		if(num!=1) {
			System.out.println(den+"/"+num+"\n");//如果分子不为1,则直接分子分母对调
		}else {
			System.out.println(den+"\n");//如果分子为1,则倒数是分母本身
		}
	}
}