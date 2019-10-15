class MatrixMultiply {

   double a[ ][ ];
   double b[ ][ ];
   double c[ ][ ];
   int cColLB; int cColUB;
   int cRowLB; int cRowUB;

   public MatrixMultiply(double a[ ][ ], double b[ ][ ], double c[ ][ ], 
                        int colsPartitions, int thisColsPartition, 
                        int rowsPartitions, int thisRowsPartition) {

      this.a = a;
      this.b = b;
      this.c = c;
      partition(rowsPartitions, thisRowsPartition, colsPartitions, thisColsPartition, c);
   }

   private int partitionLB(int numPartitions, int thisPartition, int length)  {
      int lb = (thisPartition*length)/numPartitions; 
      return lb;
   }

   private int partitionUB(int numPartitions, int thisPartition, int length) {
      int ub = ((thisPartition+1)*length)/numPartitions - 1;
      return ub;
   }

   private void partition(int rowsPartitions, int thisRowsPartition, 
                         int colsPartitions, int thisColsPartition,
                         double a[ ][ ]) {
      cRowLB = partitionLB(rowsPartitions, thisRowsPartition, a.length);
      cRowUB = partitionUB(rowsPartitions, thisRowsPartition, a.length);
      cColLB = partitionLB(colsPartitions, thisColsPartition, a[0].length);
      cColUB = partitionUB(colsPartitions, thisColsPartition, a[0].length);
   }

   public void mm( ) {
      for (int i = cRowLB; i < cRowUB+1; i++) {
         for (int j = cColLB; j < cColUB+1; j++) {
            int cij = 0;
            for (int k = 0; k < b.length; k++) {
               cij += a[i][k]*b[k][j];
            }
            c[i][j]+= cij;
         }
      }
   }

  public String toString( ) {
     String matrixMultiply = "c[" + c.length + "][" + c[0].length+ "] = " +
                             "a[" + a.length + "][" + a[0].length + "] X " +
                             "b[" + b.length + "][" + cColLB + ":" + cColUB + "]\n";

     matrixMultiply += "c[" + cRowLB + ":"+cRowUB + "][" +cColLB + ":"+ cColUB +" ] = "+
                       "a[" + cRowLB + ":" + cRowUB +"][0:" + b.length +"] X "+
                    "b[0:" + b.length +"][" +cColLB + ":" +cColUB + "]";
      return matrixMultiply;
   }
}
         
