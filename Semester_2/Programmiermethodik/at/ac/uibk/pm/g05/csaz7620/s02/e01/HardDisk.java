package at.ac.uibk.pm.g05.csaz7620.s02.e01;

public class HardDisk {
    private String name;
    private HardDiskType hardDiskType;
    private int storageCapacity;
    private int dataWriteRate;
    private int price;

    public HardDisk(String name, HardDiskType hardDiskType, int storageCapacity, int dataWriteRate, int price) {
        setName(name);
        setHardDiskType(hardDiskType);
        setStorageCapacity(storageCapacity);
        setDataWriteRate(dataWriteRate);
        setPrice(price);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public HardDiskType getHardDiskType() {
        return hardDiskType;
    }

    public void setHardDiskType(HardDiskType hardDiskType) {
        this.hardDiskType = hardDiskType;
    }

    public int getStorageCapacity() {
        return storageCapacity;
    }

    public void setStorageCapacity(int storageCapacity) {
        this.storageCapacity = storageCapacity;
    }

    public int getDataWriteRate() {
        return dataWriteRate;
    }

    public void setDataWriteRate(int dataWriteRate) {
        this.dataWriteRate = dataWriteRate;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }
}
