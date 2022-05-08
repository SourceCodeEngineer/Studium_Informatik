package at.ac.uibk.pm.g05.csaz7620.s05.e04;

public class OrangeJuice extends Drink {

    private static String name = "orangeJuice";
    private static int price = 250;
    private static int upperLimit = 10;
    private static int lowerLimit = 5;

    @Override
    public boolean checkAmount(int amount) {
        return (amount <= upperLimit && amount >= lowerLimit);
    }

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public int getUpperLimit() {
        return upperLimit;
    }

    @Override
    public int getLowerLimit() {
        return lowerLimit;
    }
}

