package at.ac.uibk.pm.g05.csaz7620.s07.e02;

import java.util.Random;

public class ExampleGame implements Game {
    @Override
    public int compareTo(Object player1, Object player2) {
        if((player1.equals("Scissors") && player2.equals("Paper")) || (player1.equals("Stone") &&player2.equals("Scissors")) || (player1.equals("Paper") &&player2.equals("Stone"))){
            return 1;
        }
        if(player1.equals(player2)){
            return 0;
        }
        else {
            return -1;
        }
    }

    @Override
    public Object randomValues() {
        Random rand = new Random();
        int x = rand.nextInt(3);
        if(x == 1) {
            return "Scissors";
        }
        if(x == 2) {
            return "Paper";
        }
        else{
            return "Stone";
        }
    }
}