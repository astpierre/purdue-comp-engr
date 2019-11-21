import java.rmi.*;
import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class MyRemoteClient {
   public static void main (String[ ] args) {
      new MyRemoteClient( ).go( );
   }

   public void go( ) {
      try {
         /* Start remote process */
         MyRemote service = (MyRemote)Naming.lookup("rmi://127.0.0.1/RemoteHello");
         
         /* Run hello RMI */ 
         String hello = service.sayHello( );
         System.out.println(hello);
          
         /* Run goodbye RMI */ 
         String goodbye = service.sayGoodBye( );
         System.out.println(goodbye);
         
         /* Shutdown the remote process */
         try {
            service.shutdown();
         } catch(java.rmi.UnmarshalException e) {
            System.out.println("RMI call ended unexpectedly.");
         }

         /* Attempt to access remote process services */
         try {
            service.sayHello();
         } catch(java.rmi.ConnectException e) {
            System.out.println("RMI service connection inactive.");
         }
      
      } catch (Exception ex) {
         ex.printStackTrace( );
      }
   }
} 
