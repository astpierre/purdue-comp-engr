public class VCVState extends CompilerState {

   Compiler compiler = null; 

   public VCVState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing VCVState, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String s) {
      compiler.values[++compiler.valueCount] = Integer.parseInt(s);
      compiler.state = StateFactory.getState("CVState");
   }

   public void eol( ) { 
      System.out.println("Parsing VCVState, expected value, found eol");
      // XXX compiler.targetState.eol( );
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Error in VCVState, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "VCVState";
   }
}
