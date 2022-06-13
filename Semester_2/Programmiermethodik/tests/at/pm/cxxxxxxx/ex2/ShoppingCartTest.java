package tests.at.pm.cxxxxxxx.ex2;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.function.Executable;

import static org.junit.jupiter.api.Assertions.*;


/**
 * This class contains tests to check the shopping-cart functionality
 *
 * @author PM-Team
 */
public class ShoppingCartTest {

    /**
     * Tests the insertion of an item
     */
    @Test
    public void testAddItem() {
        ShoppingCart shoppingCart = new ShoppingCart();

        Item itemToAdd = new Item("item0", 10);
        shoppingCart.addItem(itemToAdd, 2);

        ItemEntry itemEntry = shoppingCart.getItemEntry(itemToAdd);
        assertAll(
                () -> assertNotNull(itemEntry),
                () -> assertEquals(itemToAdd, itemEntry.getItem()),
                () -> assertEquals(2, shoppingCart.getTotalAmountOfItems())
        );

    }

    /**
     * Tests the insertion of an item with negative amount
     */
    @Test
    public void testAddItemIllegalArgument() {
        ShoppingCart shoppingCart = new ShoppingCart();

        Item testItem = new Item("testItem", 3);
        Executable when = () -> shoppingCart.addItem(testItem, -1);

        assertThrows(IllegalArgumentException.class, when);
    }

    /**
     * Tests the successful removal of an item
     *
     * @throws ItemRemovalException
     */
    @Test
    public void testRemoveItem() throws ItemRemovalException {
        ShoppingCart shoppingCart = new ShoppingCart();
        Item item = new Item("item0", 10);
        shoppingCart.addItem(item, 20);

        shoppingCart.removeItem(item, 8);

        ItemEntry itemEntry = shoppingCart.getItemEntry(item);
        assertAll(
                () -> assertNotNull(itemEntry),
                () -> assertEquals(12, itemEntry.getAmount())
        );
    }

    /**
     * Tests the attempt to remove a non-existing item
     */
    @Test
    public void testRemoveItemNonExisting() {
        ShoppingCart shoppingCart = new ShoppingCart();

        Item item = new Item("item0", 10);
        Executable when = () -> shoppingCart.removeItem(item, 8);

        assertThrows(ItemRemovalException.class, when);
    }

    /**
     * Tests the calculation of the price
     */
    @Test
    public void testCalcPrice() {
        ShoppingCart shoppingCart = new ShoppingCart();
        Item item0 = new Item("item0", 10);
        Item item1 = new Item("item1", 11);
        shoppingCart.addItem(item0, 2);
        shoppingCart.addItem(item1, 2);

        double price = shoppingCart.calculatePrice();

        assertEquals(42.0, price);
    }

}
