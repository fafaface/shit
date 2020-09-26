package chapter1;
import java.util.Scanner;
public class ex5 {
	public static void main(String[] args) {//主类
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in); //创建一个Scanner
		System.out.println("请输入n: ");
		long n = sc.nextLong(); //输入一个数字
	//	long ans=n*n; 使用通项公式
      	long ans=0;
      	for(int i=1,j=1;j<=n;i+=2,++j){
          ans+=i;
        }
      
		System.out.println(ans);
	}
}