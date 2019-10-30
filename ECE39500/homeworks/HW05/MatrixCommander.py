import sys, os, time
from threading import Lock, Thread
from MatrixMultiply import MatrixMultiply


class MatrixCommander:
    def __init__(self, numThreads):
        self.num_threads = numThreads
        self.jobs = []
        self.threads = []
        self.lock = Lock()

    def doJob(self):
        while self.jobs:
            self.lock.acquire()
            if self.jobs:
                myJob = self.jobs.pop()
                self.lock.release()
                myJob.mm()
            else: self.lock.release()
        return None

    def run(self):
        start = time.time()
        for i in range(len(self.jobs)):
            t = Thread(target=self.doJob)
            self.threads.append(t)
            t.start()
        end = time.time()
        tdiff = end-start
        print(f"\tduration: {tdiff}s")
        return None


    def addJob(self, mm_obj):
        self.jobs.append(mm_obj)