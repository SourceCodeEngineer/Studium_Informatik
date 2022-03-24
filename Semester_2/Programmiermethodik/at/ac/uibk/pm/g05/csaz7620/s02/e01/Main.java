package at.ac.uibk.pm.g05.csaz7620.s02.e01;

import java.util.Date;

public class Main {

    public static void main(String[] args) {

        //PC 1 for testing purposes
        Processor processor = new Processor("TheOneAndOnly", Processortype.AMD, (short) 24, 254986);
        HardDisk hardDisk = new HardDisk("myEndlessSourceOfPain", HardDiskType.SSD, 128, 10, 51845);
        RamSlot ramslot1 = new RamSlot("theRealRamThatWasDownloaded", (short) 32, (short) 3200, 1250);
        RamSlot ramslot2 = new RamSlot("theRealRamThatWasDownloaded", (short) 32, (short) 3200, 1250);
        GPU gpu = new GPU("notYetReleased 4900 definetly not overpriced", "NVIDIA", 47483647);

        Computer myNewPC = new Computer("1", new Date(), processor, hardDisk, ramslot1, ramslot2, gpu);

        System.out.println(myNewPC.calculatePrice());

        myNewPC.printInfo();

        System.out.println("estimated data transfer duration: " + myNewPC.estimateDataTransferDuration(24));

        //PC 2 for testing purposes
        Processor processor2 = new Processor("TheOneAndOnly", Processortype.AMD, (short) 24, 254986);
        HardDisk hardDisk2 = new HardDisk("myEndlessSourceOfPain", HardDiskType.SSD, 512, 20, 51845);
        RamSlot ramslot12 = new RamSlot("theRealRamThatWasDownloaded", (short) 32, (short) 3200, 1250);
        RamSlot ramslot22 = new RamSlot("theRealRamThatWasDownloaded", (short) 32, (short) 3200, 1250);
        GPU gpu2 = new GPU("notYetReleased 4900 definetly not overpriced", "NVIDIA", 47483647);

        Computer myNewPC2 = new Computer("2", new Date(), processor2, hardDisk2, ramslot12, ramslot22, gpu2);

        System.out.println(myNewPC2.calculatePrice());

        myNewPC2.printInfo();

        System.out.println("estimated data transfer duration: " + myNewPC2.estimateDataTransferDuration(10));
    }
}
