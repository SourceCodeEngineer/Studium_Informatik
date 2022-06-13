package e02;

public interface Game<T> {

    public <T> int compareTo(T player1, T player2);    // the game must clarify which result is better
    public  T randomValues();
}
