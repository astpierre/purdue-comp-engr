class MatrixMultiply:
    def __init__(self, a, b, c, 
                 colsPartitions, 
                 thisColsPartition, 
                 rowsPartitions, 
                 thisRowsPartition):
        self.a = a
        self.b = b
        self.c = c

        self.partition(rowsPartitions, thisRowsPartition, colsPartitions, thisColsPartition, self.c)
        return

    def partitionLB(self, numPartitions, thisPartition, length):
        return ((thisPartition*length)/numPartitions)
    
    def partitionUB(self, numPartitions, thisPartition, length):
        return (((thisPartition+1)*length)/numPartitions)-1
    
    def partition(self, rowsPartitions, thisRowsPartition,
                  colsPartitions, thisColsPartition, a):
        self.cRowLB = self.partitionLB(rowsPartitions, thisRowsPartition, len(self.c))
        self.cRowUB = self.partitionUB(rowsPartitions, thisRowsPartition, len(self.c))
        self.cColLB = self.partitionLB(colsPartitions, thisColsPartition, len(self.c[0]))
        self.cColUB = self.partitionUB(colsPartitions, thisColsPartition, len(self.c[0]))
        return None
    
    def mm(self):
        for i in range(int(self.cRowLB), int(self.cRowUB+1)):
            for j in range(int(self.cColLB), int(self.cColUB+1)):
                cij = 0
                for k in range(len(self.b)):
                    cij += self.a[i][k]*self.b[k][j]
                self.c[i][j] += cij
        return None

    def __str__(self):
        mmstr = f"""c[{len(self.c)}][{len(self.c[0])}] = a[{len(self.a)}][{len(self.a[0])}] X b[{len(self.b)}][{self.cColLB}:{self.cColUB}]"""
        mmstr += f"""c[{self.cRowLB}:{self.cRowUB}][{self.cColLB}:{self.cColUB}] = a[{self.cRowLB}:{self.cRowUB}][0:{len(self.b)}] X b[0:{len(self.b)}][{self.cColLB}:{self.cColUB}]"""
        return mmstr