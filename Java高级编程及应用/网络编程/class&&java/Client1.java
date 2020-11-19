import java.net.*;
import java.io.*;

public class Client1 {
    public static void main(String[] args) {
        Socket s=null;
        InputStreamReader in=null;
        OutputStreamWriter out=null;       
        try{
            s=new Socket("localhost",8000);
            System.out.println("localhost:8000 connected......");
            out=new OutputStreamWriter(s.getOutputStream());
            int id=(int)Math.random()*10;
            String request="Client"+id;
            out.write(request,0,request.length());
            out.flush();
            System.out.println("发送的服务请求是: "+request);
            in=new InputStreamReader(s.getInputStream());
            char[] buf=new char[100];
            in.read(buf, 0, buf.length);
            String response=new String(buf);
            System.out.println("接收的服务响应是: "+ response+"其编码是: "+in.getEncoding());
        }catch(IOException  e){
            System.out.println(e.getMessage());
        }
    }
}
