interface Shape{
    public static final int x = 100;
}

class circle implements Shape{
}

class interface11{
    public static void main(String[] args){
        circle c1 = new circle();
        System.out.println(c1.x);
    }
}
