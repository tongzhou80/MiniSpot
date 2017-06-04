public class Inc {
    public boolean b; 
    public int i;
    public long l;

    public int geti() {
        return i;
    }
    
    public void addInt(int x) {
        i += x;
    }

    public void test(int x) {
        x *= 3;
        x *= 4;
    }
    
    public static void main(String[] args) {
        Inc h = new Inc();
        h.addInt(4);
        h.geti();
    }
}
