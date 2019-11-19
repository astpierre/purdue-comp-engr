public class CVCVCVState extends CompilerState {

   Compiler compiler = null; 

   public CVCVCVState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      compiler.state = StateFactory.getState("VCVCVState");
   }

   public void value(String str) {
      System.out.println("Parsing CVCVCV, expected , found int "+str);
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void eol( ) { 
      System.out.println("Parsing CVCV, expected value, found eol");
      compiler.state = StateFactory.getState("ErrorState");
   }
      
   public void eof( ) {
      System.out.println("Parsing CVCVCV, expecting value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "CVCVCVState";
   }
}
