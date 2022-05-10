package week07;

import java.util.*;

public class InvertedIndex {
    public static void main(String[] args) {
        String test = """
                Lorem ipsum dolor sit amet, consectetur adipiscing elit.
                Etiam ullamcorper consectetur orci, vel vehicula magna euismod nec.
                Etiam lacus felis, porttitor non lorem in, posuere rutrum ipsum.
                Etiam varius pellentesque sapien tempus finibus.
                Vestibulum rutrum, lacus et egestas faucibus, justo velit dignissim purus, a tempor ex velit at felis.
                Suspendisse et libero feugiat, vestibulum ex a, volutpat neque.
                In et molestie enim.
                Suspendisse tincidunt fringilla libero, ut hendrerit magna sagittis nec.
                Cras sodales augue dui, vitae rutrum ipsum consectetur eget.
                Aliquam erat volutpat.
                Vestibulum sed laoreet ante.
                Quisque hendrerit tincidunt sodales.
                Vivamus vel eros sodales, feugiat lectus et, vehicula ante.
                """;
        System.out.println(invertedIndex(test));
    }

    public static HashMap<String,ArrayList<Integer>> invertedIndex(String string) {

        HashMap<String, ArrayList<Integer>> hashMap= new HashMap<>();

        // all to lower because I don't care about upper or lower case difference
        String[] lineArray = string.toLowerCase().replaceAll("[^a-zA-Z0-9\\s\\r\\n]", "").split("\n");

        // creating double array
        String[][] wordArray = new String[lineArray.length][];

        for(int i = 0; i < lineArray.length; ++i) {

            // add every word of line i to the word array
            wordArray[i] = lineArray[i].split(" ");

            // do the loopy loop
            for(String word : wordArray[i]) {

                // create array List
                ArrayList<Integer> arrayList;

                // if hashmap doesn't contain the word do stuff
                if(!hashMap.containsKey(word)) {

                    arrayList = new ArrayList<Integer>();

                    arrayList.add(++i);

                    hashMap.put(word, arrayList);

                } else {
                    arrayList = hashMap.get(word);
                    arrayList.add(++i);
                }
            }
        }
        return hashMap;
    }
}