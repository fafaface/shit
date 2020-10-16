
public class Yanghui {
	public static void main(String[] args) {
		long n=0;
		for(String arg:args) {
			n=Integer.parseInt(arg);
		}
		long [][]data=new long[(int) n][];
		long spaces=n;
		for (int i=0; i<data.length;i++) {
				spaces-=1;
			for(int k=0;k<spaces;++k)
				System.out.print(" ");
			data[i]=new long[i+1];
			for (int j=0; j<data[i].length;j++) {
				if (i==0||j==0||i==j) {
					data[i][j] = 1;
				} else {
					data[i][j]=data[i-1][j-1]+data[i-1][j];
				}
				
				System.out.print(data[i][j]%10+" ");
			}
			System.out.println();
	
		
	}
}
	}
