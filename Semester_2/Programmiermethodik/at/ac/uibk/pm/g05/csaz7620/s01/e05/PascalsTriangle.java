package at.ac.uibk.pm.g05.csaz7620.s01.e05;

import java.util.ArrayList;
import java.util.List;

public class PascalsTriangle {

    public static List<List<Integer>> pascalsTriangle(int numRows) {

        List<List<Integer>> all_rows = new ArrayList<>(); //result
        ArrayList<Integer> row = new ArrayList<>();

        for (int i = 0; i < numRows; i++) {
            row.add(0, 1); //add element 1 at index 0.

            //now iterate the row, keep adding elements in pair, starting from j=1,
            // and set the sum at index j
            for (int j = 1; j < row.size() - 1; j++)
                row.set(j, row.get(j) + row.get(j + 1));

            //create a copy of row and store it in all_rows
            all_rows.add(new ArrayList<>(row));
        }
        return all_rows;
    }

    public static void main(String[] args){
    }
}

