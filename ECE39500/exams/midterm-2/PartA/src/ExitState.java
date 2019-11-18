public class ExitState extends CompilerState {

   Compiler compiler = null; 

   public ExitState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) {
      System.out.println(", tossing ','");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      System.out.print("In exit state, got value.");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void eol( ) {
       return;
   }
      
   public void eof( ) {
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "ErrorState";
   }
}
