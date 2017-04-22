public class Inc {
    public boolean b; 
    public int i;
    public long l;

    public Inc() {
	i = 1;
	for (int j = 0; j < 1; j++) {
	    i++;
	}
    }

    public int geti() {
	return i;
    }
    
    public int addInt(int x) {
	return x + i;
    }
    
    public static void main(String[] args) {
	Inc h = new Inc();
	h.addInt(4);
	h.geti();
    }
}
