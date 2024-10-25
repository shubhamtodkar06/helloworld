interface Vehicle {
    void gearChange(int newGear);
    void speedUp(int increament);
    void applyBrakes(int decrement);

    int getSpeed();
    int getGear();
}

class Bicycle implements Vehicle {
    int currentSpeed = 0;
    int currentGear = 0;

    @Override public void gearChange(int newGear)
    {
        this.currentGear = newGear;
        System.out.println("Bicycle Gear changed to " + newGear);
    }

    @Override public void speedUp(int increament)
    {
        this.currentSpeed += increament;
        System.out.println("Bicycle Speed increased by " + increament);
    }

    @Override public void applyBrakes(int decrement)
    {
        this.currentSpeed -= decrement;
        System.out.println("Brakes Appied : Bicycle Speed decreased by " + decrement);
    }

    @Override public int getSpeed()
    {
        return currentSpeed;
    }

    @Override public int getGear()
    {
        return currentGear;
    }
}

class Bike implements Vehicle {
    int currentSpeed = 0;
    int currentGear = 0;

    @Override public void gearChange(int newGear)
    {
        this.currentGear = newGear;
        System.out.println("Bike Gear changed to " + newGear);
    }

    @Override public void speedUp(int increament)
    {
        this.currentSpeed += increament;
        System.out.println("Bike Speed increased by " + increament);
    }

    @Override public void applyBrakes(int decrement)
    {
        this.currentSpeed -= decrement;
        System.out.println("Brakes Appied : Bike Speed decreased by " + decrement);
    }

    @Override public int getSpeed()
    {
        return currentSpeed;
    }

    @Override public int getGear()
    {
        return currentGear;
    }
}

class Car implements Vehicle {
    int currentSpeed = 0;
    int currentGear = 0;

    @Override public void gearChange(int newGear)
    {
        this.currentGear = newGear;
        System.out.println("Car Gear changed to " + newGear);
    }

    @Override public void speedUp(int increament)
    {
        this.currentSpeed += increament;
        System.out.println("Car Speed increased by " + increament);
    }

    @Override public void applyBrakes(int decrement)
    {
        this.currentSpeed -= decrement;
        System.out.println("Car Appied : Bicycle Speed decreased by " + decrement);
    }

    @Override public int getSpeed()
    {
        return currentSpeed;
    }

    @Override public int getGear()
    {
        return currentGear;
    }
}

class interFace {
    public static void main(String[] args)
    {

        System.out.println("For Car :");
        Car car = new Car();
        car.gearChange(3);
        car.speedUp(50);
        car.applyBrakes(16);

        int speed = car.getSpeed();
        int gear = car.getGear();

        System.out.println("Speed of Car : " + speed);
        System.out.println("Gear of Car : " + gear);
        System.out.println("");

        System.out.println("For Bike :");
        Bike bike = new Bike();
        bike.gearChange(3);
        bike.speedUp(50);
        bike.applyBrakes(16);

        int speed1 = bike.getSpeed();
        int gear1 = bike.getGear();

        System.out.println("Speed of Bike : " + speed1);
        System.out.println("Gear of Bike : " + gear1);
    }
}
