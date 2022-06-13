package at.ac.uibk.pm.g05.csaz7620.s07.e01;

public class Item extends Entity{
    private long id;
    private String name;
    private int price;

    public Item(long id, String name, int price) {
        super(name + " " + price,id);
    }
}
