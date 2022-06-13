package at.ac.uibk.pm.g05.csaz7620.s08.e02;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.math.BigDecimal;
import java.math.MathContext;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;


public class InventoryTest {

    private ArrayList<Item> items = new ArrayList<>();

    @BeforeEach
    public void initEach() {
        Item apple = new Item("apple", FoodType.FRUIT, new BigDecimal(20), LocalDate.now().minusDays(5));
        Item ribs = new Item("ribs", FoodType.MEAT, new BigDecimal(200), LocalDate.now().plusDays(50));
        Item candy = new Item("candy", FoodType.SWEETS, new BigDecimal(50), LocalDate.now().plusDays(1000));
        Item banana = new Item("banana", FoodType.FRUIT, new BigDecimal(20), LocalDate.now().minusDays(5));
        Item hotDog = new Item("hotDog", FoodType.MEAT, new BigDecimal(150), LocalDate.now().plusDays(1));
        Item strawberry = new Item("strawberry", FoodType.FRUIT, new BigDecimal(10), LocalDate.now().plusDays(5));
        Item salami = new Item("salami", FoodType.MEAT, new BigDecimal(70), LocalDate.now().minusDays(5));

        items.add(apple);
        items.add(ribs);
        items.add(candy);
        items.add(banana);
        items.add(hotDog);
        items.add(strawberry);
        items.add(salami);
    }

    @Test
    public void getItemsTest() {
        Inventory inventory = new Inventory(items);
        List<Item> x = inventory.getItems(FoodType.FRUIT, new BigDecimal(200));
        boolean result = x.stream().allMatch(i -> (i.getFoodType() == FoodType.FRUIT) && (i.getPrice().compareTo(new BigDecimal(200)) < 0));
        Assertions.assertTrue(result);
    }

    @Test
    public void getItemsTestOnlyFoodTypeTest() {
        Inventory inventory = new Inventory(items);
        List<Item> x = inventory.getItems(FoodType.FRUIT);
        boolean result = x.stream().allMatch(i -> (i.getFoodType() == FoodType.FRUIT));
        Assertions.assertTrue(result);
    }

    @Test
    public void getTotalPriceTest() {
        Inventory inventory = new Inventory(items);
        BigDecimal totalPrice = inventory.getTotalPrice();
        List<Item> allItems = inventory.getAllItems();
        BigDecimal checkTotalPrice = new BigDecimal(0);
        for (Item item : allItems) {
            checkTotalPrice = checkTotalPrice.add(item.getPrice());
        }
        Assertions.assertTrue(checkTotalPrice.equals(totalPrice));
    }

    @Test
    public void getTotalPriceOfFoodTypeTest() {
        Inventory inventory = new Inventory(items);
        BigDecimal totalPrice = inventory.getTotalPrice(FoodType.FRUIT);
        List<Item> allItems = inventory.getItems(FoodType.FRUIT);
        BigDecimal checkTotalPrice = new BigDecimal(0);
        for (Item item : allItems) {
            checkTotalPrice = checkTotalPrice.add(item.getPrice());
        }
        Assertions.assertTrue(checkTotalPrice.equals(totalPrice));
    }

    @Test
    public void getAveragePriceTest() {
        Inventory inventory = new Inventory(items);
        BigDecimal averagePrice = inventory.getAveragePrice(FoodType.FRUIT);
        List<Item> allItems = inventory.getItems(FoodType.FRUIT);
        BigDecimal totalPrice = new BigDecimal(0);
        for (Item item : allItems) {
            totalPrice = totalPrice.add(item.getPrice());
        }
        BigDecimal averagePriceTest = totalPrice.divide(new BigDecimal(allItems.size()), MathContext.DECIMAL128);
        Assertions.assertTrue(averagePrice.equals(averagePriceTest));
    }

    @Test
    public void sortItemsPerPriceTest() {
        Inventory inventory = new Inventory(items);
        List<Item> allItems = inventory.getAllItems();

        Collections.sort(allItems, new Comparator<Item>() {
            @Override
            public int compare(Item o1, Item o2) {
                BigDecimal bigDecimal1 = o1.getPrice();
                BigDecimal bigDecimal2 = o2.getPrice();
                int res = bigDecimal1.compareTo(bigDecimal2);
                return res;
            }
        });
        inventory.sortItemsByPrice();
        Assertions.assertEquals(inventory.getAllItems(), allItems);

    }

    @Test
    public void sortItemsPerPriceTest2() {
        Inventory inventory = new Inventory(items);
        inventory.sortItemsByPrice();
        List<Item> allItems = inventory.getAllItems();
        Assertions.assertTrue((allItems.get(0).getPrice().compareTo(allItems.get(1).getPrice())) < 0);
    }

    @Test
    public void sortItemPerFoodType() {
        Inventory inventory = new Inventory(items);
        List<Item> allItems = inventory.getAllItems();

        Collections.sort(allItems, new Comparator<Item>() {
            @Override
            public int compare(Item o1, Item o2) {
                FoodType foodType1 = o1.getFoodType();
                FoodType foodType2 = o2.getFoodType();
                int res = foodType1.compareTo(foodType2);
                return res;
            }
        });
        inventory.sortItemsByFoodType();
        Assertions.assertEquals(inventory.getAllItems(), allItems);
    }

    @Test
    public void getAllItemsAlphabetically() {
        Inventory inventory = new Inventory(items);
        List<Item> allItems = inventory.getAllItems();

        Collections.sort(allItems, new Comparator<Item>() {
            @Override
            public int compare(Item o1, Item o2) {
                String name1 = o1.getName();
                String name2 = o2.getName();
                int res = name1.compareTo(name2);
                return res;
            }
        });
        List<Item> allItemsTest = inventory.getAllItemsAlphabetically();
        Assertions.assertEquals(allItemsTest, allItems);
    }

    @Test
    public void getAllItemsAlphabetically2() {
        Inventory inventory = new Inventory(items);
        List<Item> allItems = inventory.getAllItemsAlphabetically();
        Assertions.assertTrue((allItems.get(0).getName().compareTo(allItems.get(1).getName())) < 0);
    }
}

