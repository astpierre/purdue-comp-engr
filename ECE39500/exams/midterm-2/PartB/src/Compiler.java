import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Compiler {

   // ld0 regi
   // addi regi, int
   // add regi, regj, regk // regi = regj + regk
   // print regi
   // halt

   public static final boolean DEBUG = false;

   public static int valueCount = -1;
   public static int[ ] values = {Integer.MIN_VALUE, Integer.MIN_VALUE, 
                                  Integer.MIN_VALUE};

   public static CompilerState targetState = null;
   public static CompilerState state = null;

   public Compiler( ) { }

   public void compile(String fileName) {
      state = StateFactory.getState("InitState");
      BufferedReader reader = null;
      try {
         reader = new BufferedReader(new FileReader(fileName));
         String line = reader.readLine();
         while (line != null) {
            parseLine(line);
            line = reader.readLine();
         }
         state.eof( ); // CHANGED
      } catch (IOException e) {
         e.printStackTrace();
      } finally {
         try {
            if (reader == null) {
               System.out.println("file "+fileName+" not opened");
            } else {
               reader.close();
            }
         } catch (IOException e) {e.printStackTrace( );}
      }
   }

   private void parseLine(String line) {
      if (DEBUG) {
         System.out.println("\nParsing input line: "+line);
      }

      line = line.trim( );
      line = line.replaceAll(",", " , ");
      line = line.replaceAll("\\s+", " ");
      String[ ] tokens = line.split("\\s");
      
      for (int i = 0; i < tokens.length; i++) {
         takeAction(tokens[i]); 
      }
      state.eol( );
   }

   private void takeAction(String token) {
      if (DEBUG) {
         System.out.println("Taking action with state "+state);
      }
      if (token.matches("[+-]?[0-9][0-9]*")) { 
        state.value(token);
      } else if (token.matches("addi|ld0|add|print|exit|store")) {
         for (int i = 0; i < 3; i++) {
            values[i] = Integer.MIN_VALUE;
         }
         valueCount = -1;
         state.value(token);
      } else if (token.equals(",")) {
         state.comma( );
      } else {
         System.out.println("Unknown token ::" + token+"::"); 
         state = StateFactory.getState("ErrorState");
      }
   }
}
