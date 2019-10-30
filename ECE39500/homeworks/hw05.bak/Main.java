import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import mcommander.*;
import mmul.*;

class Main {
  public static void main(String[] args) {

    int cRows1 = 1000;
    int cCols1 = 4000;
    int n = 300;
    int rowPartitions = 2;
    int colPartitions = 2;

    double a[ ][ ] = new double[cRows1][n];
    double b[ ][ ] = new double[n][cCols1];
    double c[ ][ ] = new double[cRows1][cCols1];

    ArrayList<MatrixMultiply> partitionedArrays = null;
    MatrixCommander matrixCommander = new MatrixCommander(1);

    initArray(a, 1.0);
    initArray(b, 1.0);
    initArray(c, 0.0);

    // printArray("Initialized a", a, true, 10);
    // printArray("Initialized b", b, true, 10);
    // printArray("Initialized c", c, true, 10);

    partitionedArrays = partitionArrays(a, b, c, rowPartitions, colPartitions);
    Iterator<MatrixMultiply> iter = partitionedArrays.iterator( );
    while (iter.hasNext( )) {
      matrixCommander.addJob(iter.next( ));
    }
    //multiplyArrays(partitionedArrays);

    printArray("Result in C: ", c, true, 10);
  }
  
  public static void initArray(double a[ ][ ], double val) {
    double init = val;
    for (int i = 0; i < a.length; i++) {
      for (int j = 0; j < a[0].length; j++) {
        a[i][j] = init; 
      }
    }
  }

  public static ArrayList<MatrixMultiply> partitionArrays(double a[ ][ ], 
                                                          double b[ ][ ],
                                                          double c[ ][ ],
                                                          int rowPartitions, 
                                                          int colPartitions) { 
    
    ArrayList<MatrixMultiply> partitionedArrays = new ArrayList<MatrixMultiply>( );

    for (int rowPartition=0; rowPartition < rowPartitions; rowPartition++) {
      for (int colPartition=0; colPartition < colPartitions; colPartition++) {
        MatrixMultiply mm = new MatrixMultiply(a, b, c, 
                                               colPartitions, colPartition,
                                               rowPartitions, rowPartition);
        partitionedArrays.add(mm);
      }
    }
    return partitionedArrays;
  }

  public static void multiplyArrays(ArrayList<MatrixMultiply> partitionedArrays) {
    long startTime = System.nanoTime( ); 

    Iterator<MatrixMultiply> iter = partitionedArrays.iterator( );
    while (iter.hasNext( )) {
      iter.next( ).mm( );
    }

    long endTime = System.nanoTime( );

    System.out.println("Execution time in milliseconds: " + ((endTime-startTime)/1000000));
  }

  public static void printArray(String label, double a[ ][ ], 
                                 boolean sparse, int numElements) {
    int rowStep = 1;
    int colStep = 1;
     
    if (sparse) {
      rowStep = a.length / numElements;
      colStep = a[0].length / numElements;
    }
     
    System.out.println(label);
     
    for (int i = 0; i < a.length; i+= rowStep) {
      for (int j = 0; j < a[0].length; j+= colStep) {
        System.out.print("" + a[i][j] + " ");
      }
      System.out.println(" ");
    }
  }
}


public class MatrixCommander {
  private final BlockingQueue<MatrixMultiply> jobQueue;
  private final Thread[] jobThreads;
  private volatile boolean shutdown;


  public MatrixCommander(int n) {
    jobQueue = new LinkedBlockingQueue<>();
    jobThreads = new Thread[n];

    for (int i = 0; i < n; i++) {
      jobThreads[i] = new Worker("Pool Thread " + i);
      jobThreads[i].start();
    }
  }


  public void addJob(MatrixMultiply mm) {
    try {
      jobQueue.put(mm);
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
  }


  public void shutdownPool() {
    while (!jobQueue.isEmpty()) {
      try {
        Thread.sleep(1000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
    shutdown = true;
    for (Thread workerThread : jobThreads) {
      workerThread.interrupt();
    }
  }


  private class Worker extends Thread {
    public Worker(String name) {
      super(name);
    }

    public void run() {
      while (!shutdown) {
        try {
          MatrixMultiply m = jobQueue.take();
          m.mm();
        } catch (InterruptedException e) {
        }
      }
    }
  }
}