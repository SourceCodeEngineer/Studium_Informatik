package tests.at.pm.cxxxxxxx.ex2;

/**
 * A class representing an item
 *
 * @author PM-Team
 */
public class Item {

    private static int idCounter = 0;
    private int id;
    private String name;
    private long price;

    public Item(String name, long price) {
        this.id = idCounter++;
        this.name = name;
        this.price = price;
    }

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @return the price
     */
    public long getPrice() {
        return price;
    }

    /**
     * @param price the price to set
     */
    public void setPrice(long price) {
        this.price = price;
    }

}
