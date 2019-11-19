public class InitState extends CompilerState {

   Compiler compiler = null; 

   public InitState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsint InitState, expected command, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      compiler.state = StateFactory.getState(str);
      compiler.targetState = compiler.state;
      if (Compiler.DEBUG) {
         System.out.println("Init to "+compiler.targetState+" transition");
      }
   }

   public void eol( ) { 
      System.out.println("Error in InitState, expected value, found eol");
      // XXX  compiler.targetState.eol( );
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Error in addi, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "InitState";
   }
}
