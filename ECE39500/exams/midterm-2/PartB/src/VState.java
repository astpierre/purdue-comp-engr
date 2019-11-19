public class VState extends CompilerState {

   Compiler compiler = null; 

   public VState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing VState, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String s) {
      compiler.values[++compiler.valueCount] = Integer.parseInt(s);
      compiler.state = compiler.targetState;
   }

   public void eol( ) { 
      System.out.println("Parsing VState, expected value, found eol");
      // XXX compiler.targetState.eol( );
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Error in VState, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "VCVState";
   }
}
