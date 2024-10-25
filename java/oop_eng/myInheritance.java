import java.util.Scanner;

class Employee
{
    String Emp_name, Emp_id, Address, Mail_id;
    int Mobile_no;
    double basicPay;

    Employee(String Emp_name, String Emp_id, String Address, String Mail_id, int Mobile_no, double basicPay)
    {
        this.Emp_name = Emp_name;
        this.Emp_id = Emp_id;
        this.Address = Address;
        this.Mail_id = Mail_id;
        this.Mobile_no = Mobile_no;
        this.basicPay = basicPay;
    }

    public void generatePaySlip()
    {
        double da = basicPay * 0.97;
        double hra = basicPay * 0.10;
        double staffClubFund = basicPay * 0.001;
        double pf = basicPay * 0.12;

        double grossSalary = basicPay + da + hra;
        double netSalary = grossSalary - staffClubFund - pf;

        System.out.println("Pay Slip for " + Emp_name);
        System.out.println("Basic Pay: " + basicPay);
        System.out.println("Dearness Allowance (DA): " + da);
        System.out.println("House Rent Allowance (HRA): " + hra);
        System.out.println("Provident Fund (PF): " + pf);
        System.out.println("Staff Club Fund: " + staffClubFund);
        System.out.println("Gross Salary: " + grossSalary);
        System.out.println("Net Salary: " + netSalary);

    }

}

class Programmer extends Employee
{
    Programmer(String Emp_name, String Emp_id, String Address, String Mail_id, int Mobile_no, double basicPay)
    {
        super(Emp_name, Emp_id, Address, Mail_id, Mobile_no, basicPay);
    }
}

class teamLeader extends Employee
{
    teamLeader(String Emp_name, String Emp_id, String Address, String Mail_id, int Mobile_no, double basicPay)
    {
        super(Emp_name, Emp_id, Address, Mail_id, Mobile_no, basicPay);
    }

}

class assistantProjectManager extends Employee
{
    assistantProjectManager(String Emp_name, String Emp_id, String Address, String Mail_id, int Mobile_no, double basicPay)
    {
        super(Emp_name, Emp_id, Address, Mail_id, Mobile_no, basicPay);
    }

}

class projectManager extends Employee
{
    projectManager(String Emp_name, String Emp_id, String Address, String Mail_id, int Mobile_no, double basicPay)
    {
        super(Emp_name, Emp_id, Address, Mail_id, Mobile_no, basicPay);
    }

}

class myInheritance
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Basic Salary of Employee : ");
        double pay = sc.nextDouble();
        Programmer programmer = new Programmer("John Doe", "A-101" , "123 Main St", "john@example.com", 90435345, pay);
        programmer.generatePaySlip();
        sc.close();
    }
}
