public class PrintState extends CompilerState {

   Compiler compiler = null; 

   public PrintState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing Print, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      System.out.println("print "+compiler.values[Integer.parseInt(str)]);
   }

   public void eol( ) { 
      compiler.state = StateFactory.getState("InitState");
   }
      
   public void eof( ) {
      System.out.println("Error in add, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "PrintState";
   }
}
