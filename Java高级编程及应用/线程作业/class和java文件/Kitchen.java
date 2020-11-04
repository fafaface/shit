public class Kitchen {
    private boolean hasMilkTea=false;
    private int cup=0;
    public synchronized void put(int x){
        while(hasMilkTea==true){
            try{
                wait();
            }catch(InterruptedException e){}
        }
        cup=x;
        hasMilkTea=true;
        notifyAll();
    }
    public synchronized int get(){
        while(hasMilkTea!=true){
            try{
                wait();
            }catch(InterruptedException e){}
        }
        int x=cup;
        hasMilkTea=false;
        notifyAll();
        return x;
    }
}
