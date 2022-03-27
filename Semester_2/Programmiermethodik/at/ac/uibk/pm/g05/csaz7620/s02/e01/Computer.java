package at.ac.uibk.pm.g05.csaz7620.s02.e01;

import java.util.Date;

public class Computer {
    private String identifier;
    private Date manufactoringDate;
    private Processor processor;
    private HardDisk hardDisk;
    private RamSlot ramSlot1, ramSlot2;
    private GPU gpu;

    public Computer(String identifier, Date manufactoringDate, Processor processor, HardDisk hardDisk, RamSlot ramSlot1, RamSlot ramSlot2, GPU gpu) {
        setIdentifier(identifier);
        setManufactoringDate(manufactoringDate);
        setProcessor(processor);
        setHardDisk(hardDisk);
        setRamSlot1(ramSlot1);
        setRamSlot2(ramSlot2);
        setGpu(gpu);
    }

    public String getIdentifier() {
        return identifier;
    }

    public void setIdentifier(String identifier) {
        this.identifier = identifier;
    }

    public Date getManufactoringDate() {
        return manufactoringDate;
    }

    public void setManufactoringDate(Date manufactoringDate) {
        this.manufactoringDate = manufactoringDate;
    }

    public Processor getProcessor() {
        return processor;
    }

    public void setProcessor(Processor processor) {
        this.processor = processor;
    }

    public HardDisk getHardDisk() {
        return hardDisk;
    }

    public void setHardDisk(HardDisk hardDisk) {
        this.hardDisk = hardDisk;
    }

    public RamSlot getRamSlot1() {
        return ramSlot1;
    }

    public void setRamSlot1(RamSlot ramSlot1) {
        this.ramSlot1 = ramSlot1;
    }

    public RamSlot getRamSlot2() {
        return ramSlot2;
    }

    public void setRamSlot2(RamSlot ramSlot2) {
        this.ramSlot2 = ramSlot2;
    }

    public GPU getGpu() {
        return gpu;
    }

    public void setGpu(GPU gpu) {
        this.gpu = gpu;
    }

    public int calculatePrice() {
        return processor.getPrice() + hardDisk.getPrice() + ramSlot1.getPrice() + ramSlot2.getPrice() + gpu.getPrice();
    }

    public void printInfo() {
        System.out.println("Id is: " + getIdentifier());
        System.out.println("Processor name: " + processor.getName());
        System.out.println("Processor-type: " + processor.getType());
        System.out.println("Number of cores: " + processor.getCores());
        System.out.println("Price of processor: " + processor.getPrice());
        System.out.println(" ");
        System.out.println("HardDisk name: " + hardDisk.getName());
        System.out.println("HardDisk type: " + hardDisk.getHardDiskType());
        System.out.println("HardDisk storage capacity: " + hardDisk.getStorageCapacity());
        System.out.println("HardDisk data write rate (GB/s): " + hardDisk.getDataWriteRate());
        System.out.println("HardDisk cost: " + hardDisk.getPrice());
        System.out.println(" ");
        System.out.println("Ram model 1 name: " + ramSlot1.getModel());
        System.out.println("Ram model 1 capacity (GB): " + ramSlot1.getCapacity());
        System.out.println("Ram model 1 clock rate (MHz): " + ramSlot1.getClockRate());
        System.out.println("Ram model 1 price: " + ramSlot1.getPrice());
        System.out.println(" ");
        System.out.println("Ram model 2 name: " + ramSlot2.getModel());
        System.out.println("Ram model 2 capacity (GB): " + ramSlot2.getCapacity());
        System.out.println("Ram model 2 clock rate (MHz): " + ramSlot2.getClockRate());
        System.out.println("Ram model 2 price: " + ramSlot2.getPrice());
        System.out.println(" ");
        System.out.println("GPU model identifier: " + gpu.getModel());
        System.out.println("GPU manufacturer name: " + gpu.getManufacturer());
        System.out.println("GPU price in cent: " + gpu.getPrice());
    }

    public double estimateDataTransferDuration(int dataToTransferInGB) {
        return dataToTransferInGB / (hardDisk.getDataWriteRate());
    }
}
