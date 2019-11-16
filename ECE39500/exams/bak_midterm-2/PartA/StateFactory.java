import java.util.*;
import java.lang.reflect.*;

public class StateFactory {

   private Compiler compiler;
   private static String[ ] classes = {"AddState", "CVCVState", "EofState", 
                                       "ErrorState", "InitState", "VCVState"};

   // used to decode command names to the corresponding class name
   private static String[ ] commands = {"add", "CVCVState", "EofState", 
                                        "ErrorState", "InitState", "VCVState"};

   private static Map<String,CompilerState> states = 
      new HashMap<String,CompilerState>( );

   public StateFactory(Compiler compiler) {
      for (int i = 0; i < classes.length; i++ ) {

         Class<?> cls = null;
         Constructor<?> constructor = null;
         CompilerState state = null;

         try {
            cls = Class.forName(classes[i]);
         } catch (ClassNotFoundException e) {
            System.out.println("forName: "+classes[i]);
            e.printStackTrace( );
         }
         
         try {
            constructor = cls.getConstructor(Compiler.class);
         } catch (NoSuchMethodException e) {
            System.out.println("getConstructor: "+classes[i]);
            e.printStackTrace( );
         }

         try {
            state = (CompilerState) constructor.newInstance(compiler); 
            states.put(commands[i], state);
            if (Compiler.DEBUG) {
              System.out.println("Initializing state "+commands[i]+", status " + (state != null));
            }
         } catch (InstantiationException | IllegalAccessException | InvocationTargetException e) {
            System.out.println("newInstance: "+classes[i]);
            e.printStackTrace( );
         }
      }
   }

   public static CompilerState getState(String state) {
      CompilerState obj = states.get(state);
      if (obj == null) {
         System.out.println("Error getting state for class "+state); 
      }
      return obj;
   }
}
