package at.ac.uibk.pm.g05.csaz7620.s04.e04;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class ItemTest {

    @Test
    void invalidItem() {
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            Item item = new Item("", 20);
        });
        String expectedMessage = "name must not be empty!";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);

        Exception exception2 = assertThrows(IllegalArgumentException.class, () -> {
            Item item = new Item(null, 20);
        });
        String expectedMessage2 = "name is null!";
        String exceptionMessage2 = exception2.getMessage();
        assertEquals(expectedMessage2, exceptionMessage2);

    }

    @Test
    void invalidPrice() {
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            Item item = new Item("MyItem", 0);
        });
        String expectedMessage = "price must not be zero!";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);
    }

    @Test
    void getName() {
        Item item = new Item("MyItem", 5);
        assertEquals("MyItem", item.getName());
    }

    @Test
    void getPrice() {
        Item item = new Item("MyItem", 5);
        assertEquals(5, item.getPrice());
    }
}
