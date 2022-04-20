package at.ac.uibk.pm.g05.csaz7620.s04.e04;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class ItemManagerTest {
    Item myItem = new Item("myItem", 100);
    Item sunglasses = new Item("sunglasses", 200);
    Item mug = new Item("mug", 100);
    Item apple2000 = new Item("The new Apple 2000 with 20% more Apple", 200);

    @Test
    void testConstructor() {
        ArrayList<Item> items = new ArrayList<>();
        items.add(myItem);

        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            ItemManager itemManager = new ItemManager(items, -2);
        });
        String expectedMessage = "The maximum size is lesser then zero";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);

        Exception exception2 = assertThrows(IllegalArgumentException.class, () -> {
            ItemManager itemManager = new ItemManager(items, 0);
        });
        String expectedMessage2 = "The maximum size is lesser then the number of Items";
        String exceptionMessage2 = exception2.getMessage();
        assertEquals(expectedMessage2, exceptionMessage2);
    }

    @Test
    void addItem() throws Exception {
        ArrayList<Item> items = new ArrayList<>();
        items.add(myItem);
        items.add(sunglasses);
        ItemManager itemManager = new ItemManager(items, 2);

        Exception exception = assertThrows(Exception.class, () -> {
            itemManager.addItem(mug);
        });
        String expectedMessage = "maximum reached";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);

        ItemManager itemManager1 = new ItemManager(items, 3);
        assertEquals(2, itemManager1.getSize());
        itemManager1.addItem(mug);
        assertEquals(3, itemManager1.getSize());
    }

    @Test
    void removeItem() {
        ArrayList<Item> items = new ArrayList<>();
        items.add(myItem);
        items.add(sunglasses);
        ItemManager itemManager = new ItemManager(items, 2);

        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () -> {
            itemManager.removeItem(mug);
        });
        String expectedMessage = "The item does not exist in this list";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);

        ItemManager itemManager1 = new ItemManager(items, 3);
        assertEquals(2, itemManager1.getSize());
        itemManager1.removeItem(sunglasses);
        assertEquals(1, itemManager1.getSize());

    }

    @Test
    void totalPrice() {
        ArrayList<Item> items = new ArrayList<>();
        items.add(myItem);
        items.add(sunglasses);
        ItemManager itemManager = new ItemManager(items, 2);

        assertEquals(itemManager.totalPrice(), (myItem.getPrice() + sunglasses.getPrice()));
        itemManager.removeItem(sunglasses);
        assertEquals(itemManager.totalPrice(), (myItem.getPrice()));
        itemManager.removeItem(myItem);
        assertEquals(itemManager.totalPrice(), 0);
    }
}
