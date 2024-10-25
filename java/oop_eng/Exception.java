class Exception{
    public static void main(String[] args){
        try{
            CheckEven(5);
        }catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }
    public static void CheckEven(int num) throws IllegalArgumentException {
            if (num % 2 != 0){
                throw new IllegalArgumentException("Odd Number");
            }
            else {
                System.out.println("Even Number");
            }
    }
}
