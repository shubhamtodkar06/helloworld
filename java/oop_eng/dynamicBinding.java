import java.util.Scanner;

abstract class Shape
{
    protected double dimension1;
    protected double dimension2;

    public Shape()
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Dimension 1 : ");
        this.dimension1 = sc.nextDouble();
        System.out.print("Enter Dimension 2 : ");
        this.dimension2 = sc.nextDouble();
    }

    public abstract double computeArea();
}

class triangle extends Shape
{
    public triangle()
    {
        super();
    }

    @Override
    public double computeArea()
    {
        return (0.5 * dimension1 * dimension2);
    }
}

class rectangle extends Shape
{
    public rectangle()
    {
        super();
    }

    @Override
    public double computeArea()
    {
        return (dimension1 * dimension2);
    }
}

class dynamicBinding
{
    public static void main(String[] args)
    {
        System.out.println("For Rectangle : ");
        rectangle rec = new rectangle();
        double area = rec.computeArea();
        System.out.println("Area of Rectangle : " + area);

        System.out.println("For Triangle : ");
        triangle tri = new triangle();
        area = tri.computeArea();
        System.out.println("Area of Triangle : " + area);
    }
}
