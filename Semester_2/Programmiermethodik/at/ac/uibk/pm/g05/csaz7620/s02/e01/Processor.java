package at.ac.uibk.pm.g05.csaz7620.s02.e01;

public class Processor {
    private String name;
    private Processortype type;
    private short cores;
    private int price;

    public Processor(String name, Processortype type, short cores, int price) {
        setName(name);
        setType(type);
        setCores(cores);
        setPrice(price);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Processortype getType() {
        return type;
    }

    public void setType(Processortype type) {
        this.type = type;
    }

    public short getCores() {
        return cores;
    }

    public void setCores(short cores) {
        this.cores = cores;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
