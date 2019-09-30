
public class LongList implements MyList {
    private LongList next;
    private long data;

    public LongList(long d) {
        next = null;
        data = d;
        return;
    }

    public LongList(LongList n, long data) {
        next =  n;
        this.data = data;
        return;
    }

    public LongList next() {  return next;  }
    public void printNode() {  System.out.println("LongList node, data is: " + getData());  }
    public long getData() {  return data;  }

}