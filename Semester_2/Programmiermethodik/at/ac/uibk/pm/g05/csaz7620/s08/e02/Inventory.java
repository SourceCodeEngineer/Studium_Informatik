package e02;

import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.time.LocalDate;
import java.time.chrono.ChronoLocalDate;
import java.util.*;
import java.util.stream.Collectors;

public class Inventory {

    private List<Item> items;

    public Inventory(List<Item> items) {
        this.items = new ArrayList<>(items);
    }

    public void addItem(Item item) {
        items.add(item);
    }

    public void removeItem(Item item) {
        items.remove(item);
    }

    public List<Item> getAllItems() {
        return new ArrayList<>(items);
    }

    public List<Item> getItems(FoodType foodType, BigDecimal priceUpperBound) {
        return items.stream().filter(c -> (c.getFoodType() == foodType) && (c.getPrice().compareTo(priceUpperBound) < 0)).collect(Collectors.toList());
    }

    public List<Item> getItems(FoodType foodType) {
        return items.stream().filter(c -> (c.getFoodType() == foodType)).collect(Collectors.toList());
    }

    public BigDecimal getTotalPrice() {
        return items.stream().map(Item::getPrice).reduce(BigDecimal.ZERO,BigDecimal::add);
    }

    public BigDecimal getTotalPrice(FoodType foodType) {
        return items.stream().filter(c ->(c.getFoodType() == foodType)).map(Item::getPrice).reduce(BigDecimal.ZERO,BigDecimal::add);
    }

    public BigDecimal getAveragePrice(FoodType foodType) {
        return getTotalPrice(foodType).divide(BigDecimal.valueOf((getItems(foodType)).size()), MathContext.DECIMAL128);
    }

    public void sortItemsByPrice() {
        Collections.sort(items,((o1, o2) -> {
            BigDecimal bigDecimal1 = o1.getPrice();
            BigDecimal bigDecimal2 = o2.getPrice();
            int res = bigDecimal1.compareTo(bigDecimal2);
            return res;
        }));
    }

    public void sortItemsByFoodType() {
        Collections.sort(items,((o1, o2) -> {
            FoodType foodType1 = o1.getFoodType();
            FoodType foodType2 = o2.getFoodType();
            int res = foodType1.compareTo(foodType2);
            return res;
        }));
    }

    public List<Item>  getAllItemsAlphabetically(){
        Collections.sort(items,(((o1, o2) -> {
            String name1 = o1.getName();
            String name2 = o2.getName();
            int res = name1.compareTo(name2);
            return res;
        })));
        return items;
    }

    public void increasePrices(){
        items.stream().filter(c ->(c.getFoodType() == FoodType.FRUIT)).peek(f -> f.setPrice(f.getPrice().multiply(BigDecimal.valueOf(1.1))));
        items.stream().filter(c ->(c.getFoodType() == FoodType.MEAT)).peek(f -> f.setPrice(f.getPrice().multiply(BigDecimal.valueOf(1.2))));
        items.stream().filter(c ->(c.getFoodType() != FoodType.FRUIT) && (c.getFoodType() != FoodType.FRUIT)).peek(f -> f.setPrice(f.getPrice().multiply(BigDecimal.valueOf(1.25))));
    }

    public List<Item> removeExpiredItems(){
        items.stream().filter(c ->(c.getExpirationDate().isBefore(LocalDate.now())));
        return items;
    }

    @Override
    public String toString() {
        return items.toString();
    }


}

