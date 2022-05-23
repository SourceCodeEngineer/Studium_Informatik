package at.ac.uibk.pm.g05.csaz7620.s07.e02;

public interface Game<T> {

    public <T> int compareTo(T player1, T player2);    // the game must clarify which result is better
    public  T randomValues();
}
