package at.ac.uibk.pm.g05.csaz7620.s07.e02;

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
