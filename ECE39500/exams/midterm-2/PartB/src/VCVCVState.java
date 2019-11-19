public class VCVCVState extends CompilerState {

   Compiler compiler = null; 

   public VCVCVState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing VCVCVState, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String s) {
      compiler.values[++compiler.valueCount] = Integer.parseInt(s);
      compiler.state = StateFactory.getState("CVCVState");
   }

   public void eol( ) { 
      System.out.println("Parsing VCVCVState, expected value, found eol");
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Error in VCVCVState, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "VCVCVState";
   }
}
