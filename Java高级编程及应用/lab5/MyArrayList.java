
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class MyArrayList {
	private static ArrayList<Integer> list;
	public static void main(String[] args) {
		boolean f=true;
		list = new ArrayList<>();
		while(f) {
			System.out.println();
			Scanner sc=new Scanner(System.in);
			String tmp=sc.nextLine();
			String arr[] = tmp.split("\\s+");   //从一行中解析出命令和参数
			String op=arr[0];
		//add_last 101	System.out.println(arr[0]+"/"+arr[1]+"/"+arr[2]+"/");
			if (op.equals("")) { 
                continue;
            }
			switch(op) {
				case "help":{
					help();
					break;
				}
				case "finish":{
					finish();
					break;
				}
				case "clear":{
					 clear();
					 break;
				}
				case "isEmpty":{
					isEmpty();
					break;
				}
				case "size":{
					size();
					break;
				}
				case "iterator":{
					iterator();
					break;
				}
				case "add_last":{
					if(!isInteger(arr[1]))
						continue;
					add_last(Integer.valueOf(arr[1]));
				break;
				}
				case "contains":{
					if(!isInteger(arr[1]))
						continue;
					contains(Integer.valueOf(arr[1]));
				break;
				}
				case "get":{
					if (!isInteger(arr[1]) || !security(Integer.valueOf(arr[1]), 1))
                        continue;
                    System.out.println("该位置的元素为: " + get(Integer.valueOf(arr[1])) + "\n");
             
				break;
				}
				case "remove":{
					if (!isInteger(arr[1]) || !security(Integer.valueOf(arr[1]), 2))
                        continue;
					remove(Integer.valueOf(arr[1]));
					break;
				}
				case "set":{
					if (!isInteger(arr[1]) || !security(Integer.valueOf(arr[1]), 3))
                        continue;
					set(Integer.valueOf(arr[1]),Integer.valueOf(arr[2]));
					break;
				}
				case "add_any":{
					if (!isInteger(arr[1]) || !security(Integer.valueOf(arr[1]), 0))
                        continue;
					add_any(Integer.valueOf(arr[1]), Integer.valueOf(arr[2]));
					break;
				}
				default:{
					warn();
					break;
				}
				
			}
		}
	}
	
	static void help() {
		System.out.println("(1)help — 不带参数。要打印出所有的命令，提示用户。\n"
				+"(2)finish — 不带参数。程序退出。\n"
				+"(3)clear — 不带参数。清空数据列表。\n"
				+"(4)isEmpty — 不带参数。返回数据列表是否为空的信息。\n"
				+"(5)size — 不带参数。返回当前数据列表的元素数目。\n"
				+"(6)iterator — 不带参数。遍历当前数据列表。\n"
				+"(7)add_last — 带一个参数。把所带的参数追加到数据列表最后。\n"
				+"(8)contains — 带一个参数。查看列表中是否含有所给的参数。\n"
				+"(9)get — 带一个参数。查看列表中的相应位置上的数据并返回。这个参数不能小于0，也不能大于或等于size，"
				+"需要对其进行判断。如果不在范围之中，则反馈给用户相应的信息。\n"
				+"(10)remove — 带一个参数。删除列表中相应位置上的信息。这个参数不能小于0，也不能大于或等于size，"
				+"需要对其进行判断。如果不在范围之中，则反馈给用户相应的信息。\n"
				+"(11)set — 带2个参数，第一个参数是位置，第二个参数是数据。把相应的位置上的数据置换成给定的第二个参数。位置范围也要判断。\n"
				+"(12)add_any — 带2个参数，在某个位置上插入一个新数据。位置范围也要判断。\n"
);
		
	}
	static void add_last(int num) {
        list.add(num);
        System.out.println("数据已经追加到列表末端");
	}
	static void add_any(int n,int num) {
		 list.add(n, num);
	     System.out.println("数据已经插入到了列表的指定位置");
	}
	static void clear() {
		list.clear();
		System.out.println("列表已经清空");
	}
	static void contains(int num) {
		System.out.println(list.contains(num)?"列表中有所给数据":"列表中没有所给数据");
	}
	static int get(int n) {
		return list.get(n);
	}
	static void isEmpty() {
		System.out.println(list.isEmpty()?"列表为空":"列表不为空");
	}
	static void remove(int n) {
		list.remove(n);
		System.out.println("给定位置的数据已从列表中删除");
	}
	static void set(int n, int num) {
		list.set(n, num);
		System.out.println("数据已经存储到了列表的指定位置");
	}
	static void size() {
		System.out.println("列表数据元素共有  " + list.size() + "个");
	}
	static void iterator() {
        System.out.print("列表数据元素列表：");
        for (int t : list) {
            System.out.print(t + " ");
        }
	}
	static void finish() {
        System.out.println("退出");
        System.exit(0);
	}
	static void warn() {
		System.out.println("输入的命令不符合规范");
	}
	static boolean security(int n, int op) {
		if( (op>0&& (n<0||n>=list.size()) )||(op==0&& (n<0||n>list.size()) )){
				switch(op) {
				case 0:{
					System.out.println("访问越界");
					break;
				}
				case 1:{
					System.out.println("获取数据位置不在范围内");
					break;
				}
				case 2:{
					System.out.println("待删数据的位置超出了范围");
					break;
				}
				case 3:{
					System.out.println("存储数据的位置超出了范围");
					break;
				}
				}
	            return false;
		}else 
			return true;
	}
	static boolean isInteger(String n) {
        Pattern pattern = Pattern.compile("-?[0-9]+");
        Matcher isNum = pattern.matcher(n);
        if (!isNum.matches()) {
            System.out.println("输入的参数不是整数");
            return false;
        }
        return true;
	}
}
