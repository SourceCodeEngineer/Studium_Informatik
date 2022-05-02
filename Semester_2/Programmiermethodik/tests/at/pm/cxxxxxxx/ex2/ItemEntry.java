package at.pm.cxxxxxxx.ex2;

/**
 * A class representing an item-entry
 *
 * @author PM-Team
 */
public class ItemEntry {

    private Item item;
    private long amount = 1;

    public ItemEntry(Item item) {
        this.item = item;
    }

    public ItemEntry(Item item, long amount) {
        this(item);
        this.amount = amount;
    }

    /**
     * Increases the item-amount
     *
     * @param amount The amount to increase
     */
    public void increaseAmount(long amount) {
        this.amount += amount;
    }

    /**
     * Decreases the item-amount
     *
     * @param amount The amount to decrease
     */
    public void decreaseAmount(long amount) {
        this.amount -= amount;
    }

    public Item getItem() {
        return item;
    }

    public long getAmount() {
        return amount;
    }

}
