package mcommander;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import mmul.*;

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
