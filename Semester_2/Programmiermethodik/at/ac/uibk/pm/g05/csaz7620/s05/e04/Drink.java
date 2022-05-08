package at.ac.uibk.pm.g05.csaz7620.s05.e04;

public abstract class Drink {

    private int price;
    private static int upperLimit;
    private static int lowerLimit;

    public abstract boolean checkAmount(int amount);

    public abstract int getPrice();

    public abstract int getUpperLimit();

    public abstract int getLowerLimit();

    @Override
    public String toString() {
        return "Drink{" +
                "price=" + price +
                '}';
    }
}
