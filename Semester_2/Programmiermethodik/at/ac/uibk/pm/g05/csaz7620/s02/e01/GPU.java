package at.ac.uibk.pm.g05.csaz7620.s02.e01;

public class GPU {
    private String model;
    private String manufacturer;
    private int price;

    public GPU(String model, String manufacturer, int price) {
        setModel(model);
        setManufacturer(manufacturer);
        setPrice(price);
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getManufacturer() {
        return manufacturer;
    }

    public void setManufacturer(String manufacturer) {
        this.manufacturer = manufacturer;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
