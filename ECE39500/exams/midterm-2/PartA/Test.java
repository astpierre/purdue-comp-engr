public class Test {

   public static void main(String args[ ]) {

      if (args.length != 1) {
         System.out.println("Test filename");
         System.exit(0);
      }
      if (Compiler.DEBUG) {
         System.out.println("Compiling "+args[0]);
      }
      Compiler compiler = new Compiler( );
      StateFactory f = new StateFactory(compiler);
      compiler.compile(args[0]);

   }
}
