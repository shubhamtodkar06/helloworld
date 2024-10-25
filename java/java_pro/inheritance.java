class Base {
    protected double i;

    public Base(double _i) {
        i = _i;
    }

    public void calculate() {
        System.out.println(i);
    }
}

class Derived extends Base {
    public Derived(double _i) {
        super(_i);
    }

    // Overloaded calculate() method with a different parameter list
    public void calculate(double pi) {
        System.out.println(i * pi);
    }
}

public class inheritance {
    public static void main(String[] args) {
        Derived d = new Derived(6.75);
        d.calculate(3.14); // Calls the overloaded calculate() method in Derived
        d.calculate(); // Calls the calculate() method inherited from Base
    }
}
