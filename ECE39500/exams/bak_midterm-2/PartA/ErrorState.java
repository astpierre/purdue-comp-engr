public class ErrorState extends CompilerState {

   Compiler compiler = null; 

   public ErrorState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) {
      System.out.print("In error state processing "+compiler.targetState.toString( ));
      System.out.println(", tossing ','");
   }

   public void value(String str) {
      System.out.print("In error state processing "+compiler.targetState.toString( ));
      System.out.println(", tossing " + str); 
   }

   public void eol( ) { 
      System.out.print("In error state processing "+compiler.targetState.toString( ));
      System.out.println("processing eol"); 
      compiler.targetState.eol( );
   }
      
   public void eof( ) {
      System.out.print("In error state processing "+compiler.targetState.toString( ));
      System.out.println("eof found, terminating compile"); 
   }

   public String toString( ) {
      return "ErrorState";
   }
}
