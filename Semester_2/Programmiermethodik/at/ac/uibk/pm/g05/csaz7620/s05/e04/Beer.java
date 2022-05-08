package at.ac.uibk.pm.g05.csaz7620.s05.e04;

public class Beer extends Drink {

    private static String name = "Beer";
    private static int price = 350;
    private static int upperLimit = 10;
    private static int lowerLimit = 1;

    public boolean checkAmount(int amount) {
        return (amount <= upperLimit && amount >= lowerLimit);
    }


    public int getPrice() {
        return price;
    }

    public int getUpperLimit() {
        return upperLimit;
    }

    public int getLowerLimit() {
        return lowerLimit;
    }
}
