package week07;

import java.util.*;

public class UniqueCharacterCount {
    static class WordCountPair implements Comparable<WordCountPair> {
        String word;
        Integer distinctCharacters;

        public WordCountPair(String word, Integer distinctCharacters) {
            this.word = word;
            this.distinctCharacters = distinctCharacters;
        }

        @Override
        public String toString() {
            return word + " " + distinctCharacters;
        }

        @Override
        public int compareTo(WordCountPair o) {
            if (this.distinctCharacters > o.distinctCharacters) {
                return -1;
            } else if (this.distinctCharacters.equals(o.distinctCharacters)){
                return 0;
            }
            return 1;
        }
    }

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
        System.out.println(wordsSortedByDistinctCharacters(test));
    }

    public static List<WordCountPair> wordsSortedByDistinctCharacters(String string) {
        // the suggested solution uses the WordCountPair class, which is provided to you
        // You do not have to use this class, if you are unhappy with this approach
        List<WordCountPair> wordUniqueCharsCountPairs = new ArrayList<>();

        // split string into substrings
        ArrayList<String> arrayList = new ArrayList<>();

        String stringWithoutNL = string.replace('\n', '.');
        stringWithoutNL = stringWithoutNL.replace('.', ',');
        stringWithoutNL = stringWithoutNL.replace(' ', ',');
        stringWithoutNL = stringWithoutNL.replaceAll(",,", ",");

        String[] stringArray = stringWithoutNL.split(",");

        for (int i = 0; i < stringArray.length; ++i){
            stringArray[i] = stringArray[i].toLowerCase();
        }

        // remove duplicates from string array
        stringArray = new HashSet<String>(Arrays.asList(stringArray)).toArray(new String[0]);

        for (String x: stringArray) {
            // returns value of the given charArray
            char[] temp = getCharArray(x.toCharArray());

            WordCountPair wcp = new WordCountPair(x, temp.length);

            wordUniqueCharsCountPairs.add(wcp);
        }

        Collections.sort(wordUniqueCharsCountPairs, WordCountPair::compareTo);

        return wordUniqueCharsCountPairs;
    }

    // get unique char array
    public static char[] getCharArray(char[] array) {
        String _array = "";
        for(int i = 0; i < array.length; ++i) {
            if(_array.indexOf(array[i]) == -1) // check if a char already exist, if not exist then return -1
                _array = _array+array[i];      // add new char
        }
        return _array.toCharArray();
    }
}
