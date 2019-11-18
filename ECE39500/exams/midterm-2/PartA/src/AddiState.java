public class AddiState extends CompilerState {

   Compiler compiler = null; 

   public AddiState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) {
       
      System.out.println("Parsing Addi, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      compiler.values[++compiler.valueCount] = Integer.parseInt(str);
   }

   public void eol( ) {
      System.out.print("reg[0] = reg["+0+"] + 5");
       compiler.state = StateFactory.getState("InitState");
   }
      
   public void eof( ) {
      System.out.println("Error in add, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "AddiState";
   }
}
