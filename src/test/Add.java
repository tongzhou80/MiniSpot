public class Add {
    public int addInt(int x, int y) {
	return x + y;
    }

    public long addLong(long x, long y) {
	return x + y;
    }
    
    public static void main(String[] args) {
	Add h = new Add();
	h.addInt(4, 5);
    }
}
