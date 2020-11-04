import java.util.Scanner;
public class MilkTea {
    public static void main(String[] args) {
        Kitchen kit=new Kitchen();
        Scanner sc=new Scanner(System.in);
        System.out.println("清华东南门的喜茶开业买一送一了, 请输入顾客数量: ");
        int n=sc.nextInt();
        int[] order=new int[n+1];
        for(int i=0;i<n;++i){
            order[i]=(int)(1+Math.random()*(11));
        }
        order[n]=-1;
        Bartender b=new Bartender(kit,order);
        SweetTooth s1=new SweetTooth(kit);
        SweetTooth s2=new SweetTooth(kit);
        SweetTooth s3=new SweetTooth(kit);
        SweetTooth s4=new SweetTooth(kit);
        SweetTooth s5=new SweetTooth(kit);
        Thread tb=new Thread(b,"顾客点奶茶, 制作");
        Thread ts1=new Thread(s1,"美团顾客领走点的奶茶");
        Thread ts2=new Thread(s2,"饿了么顾客领走点的奶茶");
        Thread ts3=new Thread(s3,"堂食顾客领走点的奶茶");
        Thread ts4=new Thread(s4,"大众点评顾客领走点的奶茶");
        Thread ts5=new Thread(s5,"喜茶go顾客领走点的奶茶");
        tb.start();ts1.start();ts2.start();ts3.start();ts4.start();ts5.start();
    } 
}
class Bartender implements Runnable{
    private Kitchen kit;
    private int[] x;//
    public Bartender(Kitchen d,int[]order){
        kit=d;
        x=order;
    }
    public void run(){
        for(int n=0;n<x.length;n++){
            System.out.println(Thread.currentThread().getName()+":"+x[n]+"杯");
            kit.put(x[n]);
            try{
                Thread.sleep(200);
            }catch(InterruptedException e){}
        }
    }
}

class SweetTooth implements Runnable{
    private Kitchen kit;
    public SweetTooth(Kitchen k){
       kit=k;
    }
    public void run(){
        while(true){
            int x=kit.get();
            if(x==-1){
                System.out.println("\t打烊了");
                return;
            }
            System.out.println("\t"+Thread.currentThread().getName()+": "+x+"杯");
            try{
                Thread.sleep((int)(1000+Math.random()*(100)));
            }catch(InterruptedException e){}
        }
    }
}