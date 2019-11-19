public class AddState extends CompilerState {

   Compiler compiler = null; 

   public AddState(Compiler compiler) {
      this.compiler = compiler;
   }

   public void comma( ) { 
      System.out.println("Parsing Add, expected int, found ,");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public void value(String str) {
      compiler.values[++compiler.valueCount] = Integer.parseInt(str);
      compiler.state = StateFactory.getState("CVCVState");
   }

   public void eol( ) { 
      if (validOperands(compiler.values, 3)) {
         System.out.print("reg["+compiler.values[2]+"] = reg[");
         System.out.print(compiler.values[0]+"] + reg[");
         System.out.println(compiler.values[1]+"]\n");
      } else {
         printInvalidOperands(compiler.values, 3);
      }
      compiler.state = StateFactory.getState("InitState");
   }
      
   public void eof( ) {
      System.out.println("Error in add, expected value, found eof");
      compiler.state = StateFactory.getState("ErrorState");
   }

   public String toString( ) {
      return "AddState";
   }
}
