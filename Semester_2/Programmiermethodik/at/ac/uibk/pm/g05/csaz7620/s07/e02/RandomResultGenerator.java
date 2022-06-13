package e02;

import java.util.Comparator;

public class RandomResultGenerator {

    private  Game game;

    public RandomResultGenerator(Game game) {
        this.game = game;
    }

    public void generateResults(Players player1, Players player2){
        ResultGenerator resultGenerator = new ResultGenerator();
        resultGenerator.generateResult(player1,player2,game);
    }
}
