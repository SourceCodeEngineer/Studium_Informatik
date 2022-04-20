package at.ac.uibk.pm.g05.csaz7620.s04.e04;

public class Item {
    private String name;
    private double price;

    public Item(String name, double price) throws IllegalArgumentException {
        try {
            if (price <= 0) {
                throw new IllegalArgumentException("price must be greater than zero");
            }
            if (name.isEmpty()) {
                throw new IllegalArgumentException("name of the item is empty");
            }
            this.name = name;
            this.price = price;
        } catch (NullPointerException e) {
            throw new IllegalArgumentException("name is null");
        }

    }

    public String getName() {
        return this.name;
    }

    public double getPrice() {
        return this.price;
    }
}

