import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.Naming;
import java.rmi.server.UnicastRemoteObject;

public class MyRemoteImpl extends UnicastRemoteObject implements MyRemote {

   public MyRemoteImpl( ) throws RemoteException { }

   public String sayHello( ) {
      return "Server says hello!";
   }

   public String sayGoodBye( ) {
      return "Server says good bye!";
   }

   public void shutdown( ) {
      System.out.println("Shutting down MyRemoteImpl.");
      System.exit(0);
   }

   public static void main (String [ ] args) {
      try {
         System.setProperty("java.rmi.server.hostname", "localhost");
         MyRemote service = new MyRemoteImpl( );

         // Bind the remote object's stub in the registry
         Naming.rebind("RemoteHello", service);
         
      } catch (Exception ex) {
         ex.printStackTrace( );
      }
   }
}
