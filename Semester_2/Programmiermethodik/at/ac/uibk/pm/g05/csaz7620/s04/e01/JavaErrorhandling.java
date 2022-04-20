package at.ac.uibk.pm.g05.csaz7620.s04.e01;

public class JavaErrorhandling {
    public static int sumPositiveInts(int... ints) {
        int sum = 0;
        for (int anInt : ints) {
            if (anInt < 0) {
                throw new IllegalArgumentException("only positive values are allowed!");
            }
            sum += anInt;
            if (sum < 0) {
                throw new RuntimeException("overflow!");
            }
        }
        return sum;
    }
}
