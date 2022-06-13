package tests.at.pm.cxxxxxxx.ex2;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

/**
 * A class implementing a basic shopping-cart functionality
 *
 * @author PM-Team
 */
public class ShoppingCart {

    private Map<Integer, ItemEntry> items = new HashMap<>();

    /**
     * Adds a certain amount of a special item to the shoppingCart
     *
     * @param item   The item
     * @param amount The amount
     */
    public void addItem(Item item, long amount) {
        // amount must be greater than 0
        if (amount <= 0) {
            throw new IllegalArgumentException();
        }
        int itemId = item.getId();
        /*
         * if not already existing => insert a new ItemEntry which holds item + amount
         */
        if (!this.items.containsKey(itemId)) {
            this.items.put(itemId, new ItemEntry(item, amount));
        }
        // already existing => just increase amount
        else {
            this.items.get(itemId)
                    .increaseAmount(amount);
        }
    }

    /**
     * Removes an item from the shopping-cart
     *
     * @param item   The item to remove
     * @param amount The amount of the item
     * @throws ItemRemovalException When a non-existing items is about to be removed
     *                              or the removal would lead to a negative amount
     */
    public void removeItem(Item item, long amount) throws ItemRemovalException {
        // amount must be greater than 0 and items must exist
        if (amount <= 0) {
            throw new IllegalArgumentException();
        }
        // If the item to remove does not exist => throw exception
        if (!this.items.containsKey(item.getId())) {
            throw new ItemRemovalException("Cannot remove non-existing item");
        }
        ItemEntry itemEntry = this.items.get(item.getId());
        // No negative amount is allowed
        if (itemEntry.getAmount() - amount < 0) {
            throw new ItemRemovalException("Cannot remove more items than exist in shopping cart");
        }
        // If amount is 0 => remove itemEntry
        else if (itemEntry.getAmount() - amount == 0) {
            this.items.remove(item.getId());
        } // simply decrease amount
        else {
            itemEntry.decreaseAmount(amount);
        }
    }

    /**
     * Calculates the price of an shopping-cart
     *
     * @return The calculated price
     */
    public double calculatePrice() {
        double totalPrice = 0.0;
        for (Entry<Integer, ItemEntry> entry : items.entrySet()) {
            ItemEntry itemEntry = entry.getValue();
            totalPrice += (itemEntry.getItem()
                    .getPrice() * itemEntry.getAmount());
        }
        return totalPrice;
    }

    /**
     * Clears the shopping-cart
     */
    public void clear() {
        this.items.clear();
    }

    /**
     * Returns the item with the corresponding id
     *
     * @param item The item
     * @return The item-entry
     */
    public ItemEntry getItemEntry(Item item) {
        return this.items.get(item.getId());
    }

    /**
     * Returns the total amount of items
     *
     * @return The total amount of items within the shoppingcart
     */
    public long getTotalAmountOfItems() {
        long totalAmount = 0;
        for (Entry<Integer, ItemEntry> entry : this.items.entrySet()) {
            totalAmount += entry.getValue()
                    .getAmount();
        }
        return totalAmount;
    }

}
