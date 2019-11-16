public class CVState extends CompilerState {

   Compiler compiler = null; 

   public CVState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      compiler.state = StateFactory.getState("VState");
   }

   public void value(String s) {
      System.out.println("Parsing CVState, expected , found int");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void eol( ) { 
      System.out.println("Parsing CVState, expected value, found eol");
      // XXX compiler.targetState.eol( );
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Error in CVState, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "CVState";
   }
}
