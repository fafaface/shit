import java.net.*;
import java.time.LocalDateTime;
import java.io.*;
public class Server1 {
    public static void main(String[] args) {
        try{
            System.out.println("TimeServer started at 8000......");
            ServerSocket ss=new ServerSocket(8000);
            while(true)
            {
                Socket s=ss.accept();
                System.out.println("收到了一个服务请求, 并建立了TCP连接: "+s.getInetAddress()+":"+s.getPort());
                timeService(s);
            }
        
        }catch(IOException e){
            System.out.println(e.getMessage());
        }

    }
    public static void timeService(Socket s){
        InputStreamReader in=null;
        OutputStreamWriter out=null;
        try{
            in=new InputStreamReader(s.getInputStream());
            char[]buf=new char[7];
            in.read(buf, 0, buf.length);
            String request=new String(buf);
            System.out.println("客户端的服务请求是"+request+"其编码是: "+in.getEncoding()+"哈希值是:"+in.hashCode());
            
            out=new OutputStreamWriter(s.getOutputStream());
            LocalDateTime t=LocalDateTime.now();
            String response=String.format("Hello, %s! %s", request,t);
            out.write(response,0,response.length());
            out.flush();
            System.out.println("返回客户端的响应是: "+response);
            
        }catch(IOException e){
            System.out.println("IOException");
        }
        
    }


}
