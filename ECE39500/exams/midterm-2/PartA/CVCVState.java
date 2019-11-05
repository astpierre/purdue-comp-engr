public class CVCVState extends CompilerState {

   Compiler compiler = null; 

   public CVCVState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      compiler.state = StateFactory.getState("VCVState");
   }

   public void value(String str) {
      System.out.println("Parsing CVCV, expected , found int "+str);
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void eol( ) { 
      System.out.println("Parsing CVCV, expected value, found eol");
      // XXX compiler.targetState.eol( );
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Parsing CVCV, expecting value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "CVCVState";
   }
}
