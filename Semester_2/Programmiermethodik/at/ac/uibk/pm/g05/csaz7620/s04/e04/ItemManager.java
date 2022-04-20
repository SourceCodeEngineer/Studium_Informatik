package at.ac.uibk.pm.g05.csaz7620.s04.e04;

import java.util.ArrayList;

public class ItemManager {
    private ArrayList<Item> items;
    private int maxSize;

    public ItemManager(ArrayList<Item> items, int maxSize) throws IllegalArgumentException {
        if (maxSize < 0) {
            throw new IllegalArgumentException("the maximum size is lesser then zero");
        }

        if (maxSize < items.size()) {
            throw new IllegalArgumentException("the maximum size is lesser then the number of Items");
        } else {
            this.items = items;
            this.maxSize = maxSize;
        }
    }

    public int getSize() {
        return items.size();
    }

    public void addItem(Item item) throws Exception {
        if (maxSize <= getSize()) {
            throw new Exception("the maximum has been reached");
        } else {
            items.add(item);
        }
    }

    public void removeItem(Item item) throws IllegalArgumentException {
        if (items.contains(item)) {
            items.remove(item);
        } else {
            throw new IllegalArgumentException("the item doesn't exist in this list");
        }
    }

    public double totalPrice() {
        double totalPrice = 0;

        for (Item item : items) {
            totalPrice = item.getPrice() + totalPrice;
        }

        return totalPrice;
    }
}
