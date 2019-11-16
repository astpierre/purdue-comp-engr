public class Ld0State extends CompilerState {

   Compiler compiler = null; 

   public Ld0State(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing Ld0, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      compiler.values[Integer.parseInt(str)] = 0;
      System.out.print("reg["+Integer.parseInt(str)+"] = 0");
   }

   public void eol( ) {
       compiler.state = StateFactory.getState("InitState");
   }
      
   public void eof( ) {
      System.out.println("Error in add, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "Ld0State";
   }
}
