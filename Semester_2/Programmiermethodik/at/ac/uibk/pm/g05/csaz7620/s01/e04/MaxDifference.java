package at.ac.uibk.pm.g05.csaz7620.s01.e04;

import static java.lang.Math.abs;

public class MaxDifference {

    public static int minValue(int[] array){
        int minValue = array[0];

        for (int i = 0; i < array.length; ++i){
            if (minValue > array[i]){
                minValue = array[i];
            }
        }
        return minValue;
    }

    public static int maxValue(int[] array){
        int maxValue = array[0];
        for (int i = 0; i < array.length; ++i){
            if (maxValue < array[i]){
                maxValue = array[i];
            }
        }
        return maxValue;
    }

    public static int maxDifference(int[] array){
        int minValue = minValue(array);
        int maxValue = maxValue(array);
        return abs(maxValue-minValue);
    }

    public static void main(String args[]){

    }
}
