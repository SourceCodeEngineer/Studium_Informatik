package at.ac.uibk.pm.g05.csaz7620.s01.e03;

import java.util.Arrays;

public class TimesTwo {

    public static void timesTwo(int value){
        System.out.println(value*2);
    }

    public  static void timesTwo(int array[]){
        for (int element:array) {
            array[element-1] *= 2;
        }
        System.out.println(Arrays.toString(array));
    }

    public static void main(String args[]){
        int[] array = {1,2,3};
        timesTwo(array);
    }
}
