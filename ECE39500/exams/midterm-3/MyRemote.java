import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MyRemote extends Remote {
   public String sayHello( ) throws RemoteException;

   public String sayGoodBye( ) throws RemoteException;

   public void shutdown( ) throws RemoteException;
}
