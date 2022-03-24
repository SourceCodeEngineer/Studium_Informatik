package at.ac.uibk.pm.g05.csaz7620.s01.e02;

public class PrintArray {

    public static void printArray(int array[][], String seperator){
        for (int[] num : array) {
            for (int elem : num) {
                System.out.print(elem);
                System.out.print(seperator);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] array = {{1, 2, 3}, {4, 5}, {6, 7, 8, 9}};
        printArray(array, " | ");
    }
}
