
public class IntList implements MyList {
    private int data;
    private IntList next;

    public IntList(int i) {
        next = null;
        data = i;
        return;
    }
    public IntList(IntList n, int i) {
        next = n;
        this.data = i;
        return;
    }

    public IntList next() {  return next;  }

    public void printNode() {  System.out.println("IntList node, data is: "+getData());  }

    public int getData() {  return data;  }
}
