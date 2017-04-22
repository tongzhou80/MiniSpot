public class Hello {
    public int foo;
    private String bar;

    public Hello() {
	foo = 100;
	bar = "Hello, fuckers.";
    }

    public void printbar() {
	System.out.println(bar);
    }

    public int add(int x, int y) {
	return x + y;
    }
    
    public static void main(int args) {
	Hello h = new Hello();
	h.add(4, 5);
	
    }
}
