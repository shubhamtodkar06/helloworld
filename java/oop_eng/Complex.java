class Complex
{
    double real;
    double imaginary;

    Complex()
    {
        this.real = 0;
        this.imaginary = 0;
    }

    Complex(double real, double imaginary)
    {
        this.real = real;
        this.imaginary = imaginary;
    }

    public void Display()
    {
        if (imaginary >= 0)
        {
            System.out.println(real + " +" + imaginary + "i");
        }
        else
        {
            System.out.println(real + " " + imaginary + "i");
        }
    }

    public Complex Add(Complex number)
    {

        double real_sum = this.real + number.real;
        double imaginary_sum = this.imaginary + number.imaginary;
        return new Complex(real_sum, imaginary_sum);
    }

    public Complex Sub(Complex number)
    {
        double real_sum = this.real - number.real;
        double imaginary_sum = this.imaginary - number.imaginary;
        return new Complex(real_sum, imaginary_sum);
    }

    public Complex Multiply(Complex number)
    {
        double real_sum = (this.real * number.real) - (this.imaginary * number.imaginary);
        double imaginary_sum = (this.real * number.imaginary) + (this.imaginary * number.real);
        return new Complex(real_sum, imaginary_sum);
    }

    public static void main(String[] args)
    {
        Complex num1 = new Complex(1, 5);
        Complex num2 = new Complex(5, -13);
        Complex num3 = new Complex();
        Complex num4 = new Complex(1,4);

        Complex result = num1.Add(num2);
        System.out.println("Sum : ");
        result.Display();

        Complex result1 = num1.Sub(num2);
        System.out.println("Sub : ");
        result1.Display();

        Complex result2 = num1.Multiply(num2);
        System.out.println("Multiply : ");
        result2.Display();

    }

}
