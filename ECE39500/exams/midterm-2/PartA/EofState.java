public class EofState extends CompilerState {

   Compiler compiler = null; 

   public EofState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing EofState, expected eol, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      System.out.println("Parsing EofState, expected eol, found value");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void eol( ) { }
      
   public void eof( ) {
      System.out.println("Parsing EofState, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }
   public String toString( ) {
      return "EofState";
   }
}
