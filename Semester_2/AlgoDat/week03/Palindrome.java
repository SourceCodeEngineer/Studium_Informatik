import java.util.ArrayList;
import java.util.List;

public class Palindrome {



  public boolean checkInput(String word) {
    word = word.replaceAll("\\s+|\\W","");
    CharStack stack = new CharStack();
    char[] wordCharArray = word.toLowerCase().toCharArray();

    // Fill stack with characters of the word
    for (char c : wordCharArray) {
      stack.push(c);
    }

    // Check whether it is a palindrom
    for (char c : wordCharArray) {
      if (c != stack.pop())
        return false;
    }

    return true;
  }

  public static void main(String[] args) {
    Palindrome pal = new Palindrome();
    

    System.out.println("Abba: " + pal.checkInput("Abba"));
    System.out.println("Rentner: " + pal.checkInput("Rentner"));
    System.out.println("Angela: " + pal.checkInput("Angela"));
    System.out.println("Lageregal:" + pal.checkInput("Lageregal"));
    System.out.println("Algorithmen und Datenstrukturen: " + pal.checkInput("Algorithmen und Datenstrukturen"));
    System.out.println("Saippuakivikauppias: " + pal.checkInput("Saippuakivikauppias"));
    System.out.println("Die Liebe ist Sieger, stets rege ist sie bei Leid.: " + pal.checkInput("Die Liebe ist Sieger, stets rege ist sie bei Leid."));
    System.out.println("Ist das die Loesung?: " + pal.checkInput("Ist das die Loesung?"));
    System.out.println("Geist ziert Leben, Mut hegt Siege, Beileid tragt belegbare Reue, Neid dient nie, nun eint Neid die Neuerer, abgelebt gart die Liebe, Geist geht, umnebelt reizt Sieg.:" + pal.checkInput("Geist ziert Leben, Mut hegt Siege, Beileid trägt belegbare Reue, Neid dient nie, nun eint Neid die Neuerer, abgelebt gärt die Liebe, Geist geht, umnebelt reizt Sieg."));

  }

  public class CharStack {
    private List<Character> stack = new ArrayList<Character>();

    public void push(char c) {
      stack.add(c);
    }

    public char pop() {
      char c = stack.get(stack.size() - 1);
      stack.remove(stack.size() - 1);
      return c;
    }

    public boolean isEmpty() {
      return stack.isEmpty();
    }

    public char top() {
      return stack.get(stack.size() - 1);
    }

    public int size() {
      return stack.size();
    }

  }

}
