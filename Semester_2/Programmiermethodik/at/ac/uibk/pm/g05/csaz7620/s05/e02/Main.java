package at.ac.uibk.pm.g05.csaz7620.s05.e02;

public class Main {

    public static void main(String[] args) {

        String text = "hallo";
        int int17 = 17;
        MyCustomClass1 mcc1a = new MyCustomClass1(17, text, 13.4, 20);
        MyCustomClass1 mcc1b = new MyCustomClass1(int17, text, 13.4, 20);
        MyCustomClass1 mcc1c = new MyCustomClass1(17, "hallo", 13.4, Integer.valueOf(20));
        MyCustomClass1 mcc1d = new MyCustomClass1(18, "hallo", 12.3, Integer.valueOf(800));
        System.out.println(mcc1a);
        System.out.println(mcc1b);
        System.out.println(mcc1c);
        System.out.println(mcc1d);
        System.out.println("mcc1a.equals(mcc1b) " + mcc1a.equals(mcc1b));
        System.out.println("mcc1a.equals(mcc1c) " + mcc1a.equals(mcc1c));
        System.out.println("mcc1a.equals(mcc1d) " + mcc1a.equals(mcc1d));
        System.out.println("\n");

        /**
         * uncomment this code block for exercise 1c
         * MyCustomClass2 mcc2a = new MyCustomClass2(17, text, 13.4, 20);
         * MyCustomClass2 mcc2b = new MyCustomClass2(int17, text, 13.4, 20);
         * MyCustomClass2 mcc2c = new MyCustomClass2(17, "hallo", 13.4,
         * Integer.valueOf(20));
         * MyCustomClass2 mcc2d = new MyCustomClass2(18, "hallo", 12.3,
         * Integer.valueOf(800));
         * System.out.println(mcc2a.toString() + mcc2b.toString() +
         * mcc2a.equals(mcc2b));
         * System.out.println(mcc2a.toString() + mcc2c.toString() +
         * mcc2a.equals(mcc2c));
         * System.out.println(mcc2a.toString() + mcc2d.toString() +
         * mcc2a.equals(mcc2d));
         */

        System.out.println("mcc1a.hashCode() " + mcc1a.hashCode());
        System.out.println("mcc1b.hashCode() " + mcc1b.hashCode());
        System.out.println("mcc1c.hashCode() " + mcc1c.hashCode());
        System.out.println("mcc1d.hashCode() " + mcc1d.hashCode());
        System.out.println();

        /**
         * uncomment this code block for exercise 1c
         * System.out.println("cs2a " + mcc2a.hashCode());
         * System.out.println("cs2b " + mcc2b.hashCode());
         * System.out.println("cs2c " + mcc2c.hashCode());
         * System.out.println("cs2d " + mcc2d.hashCode());
         */
    }

}
