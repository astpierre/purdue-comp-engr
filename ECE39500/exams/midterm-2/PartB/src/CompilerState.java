public abstract class CompilerState {
   public abstract void comma( );
   public abstract void value(String str);
   public abstract void eol( );
   public abstract void eof( );


   // check to see if parsed argument values are valid
   public boolean validOperands(int[ ] operands, int count) {
      boolean valid = true;
      for (int i = 0; i < count && valid; i++) {
         if (operands[i] == Integer.MIN_VALUE) valid = false;
      }
      return valid;
   }

   public void printInvalidOperands(int[ ] operands, int count) {
      for (int i = 0; i < count; i++) {
         if (operands[i] < 0) {
            System.out.print("Operand["+i+"], "+operands[i]);
            System.out.print(" is invalid");
         }
      }
      System.out.println(""); 
   }
}
