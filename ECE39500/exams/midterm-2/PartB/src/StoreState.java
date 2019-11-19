public class StoreState extends CompilerState {

   Compiler compiler = null; 

   public StoreState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing store, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      System.out.println("store reg["+Integer.parseInt(str)+"], ");
      compiler.state = StateFactory.getState("CVCVCVState");
   }

   public void eol( ) {
       compiler.state = StateFactory.getState("InitState");
   }
      
   public void eof( ) {
      System.out.println("Error in add, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "StoreState";
   }
}
