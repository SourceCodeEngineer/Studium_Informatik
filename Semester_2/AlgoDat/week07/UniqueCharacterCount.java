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
        return wordUniqueCharsCountPairs;
    }
}
