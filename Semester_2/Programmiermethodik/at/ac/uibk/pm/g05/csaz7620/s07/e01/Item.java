package e01;

public class Item extends Entity{
    private long id;
    private String name;
    private int price;

    public Item(long id, String name, int price) {
        super(name + " " + price,id);
    }
}
