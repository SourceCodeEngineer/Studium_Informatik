package e02;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.Objects;

public class Item {

    private final String name;
    private final FoodType foodType;
    private BigDecimal price;
    private final LocalDate expirationDate;

    public Item(String name, FoodType foodType, BigDecimal price, LocalDate expirationDate) {
        this.name = name;
        this.foodType = foodType;
        this.price = price;
        this.expirationDate = expirationDate;
    }

    public String getName() {
        return name;
    }

    public FoodType getFoodType() {
        return foodType;
    }

    public BigDecimal getPrice() {
        return price;
    }

    public void setPrice(BigDecimal price) {
        this.price = price;
    }

    public LocalDate getExpirationDate() {
        return expirationDate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof Item item)) {
            return false;
        }
        return Objects.equals(name, item.name) &&
                foodType == item.foodType &&
                Objects.equals(price, item.price) &&
                Objects.equals(expirationDate, item.expirationDate);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, foodType, price, expirationDate);
    }

    @Override
    public String toString() {
        return "%s of type %s for %s (shelf-life: %s)".formatted(name, foodType, price, expirationDate);
    }
}

