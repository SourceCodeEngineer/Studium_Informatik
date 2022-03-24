package at.ac.uibk.pm.g05.csaz7620.s02.e01;

public class RamSlot {
    private String model;
    private short capacity;
    private short clockRate;
    private int price;

    public RamSlot(String model, short capacity, short clockRate, int price) {
        setModel(model);
        setCapacity(capacity);
        setClockRate(clockRate);
        setPrice(price);
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public short getCapacity() {
        return capacity;
    }

    public void setCapacity(short capacity) {
        this.capacity = capacity;
    }

    public short getClockRate() {
        return clockRate;
    }

    public void setClockRate(short clockRate) {
        this.clockRate = clockRate;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
