package at.ac.uibk.pm.g05.csaz7620.s07.e02;

public class ResultGenerator<T> {
    public void generateResult(Players player1, Players player2, Game game) {
        T player1Value = (T) game.randomValues();
        T player2Value = (T) game.randomValues();

        if(game.compareTo(player1Value,player2Value)> 1){
            int points = player1.getPoints();
            player1.setPoints(points+3);
            player1.win();
            player2.loss();
        }
        if(game.compareTo(player1Value,player2Value) == 0){
            int points1 = player1.getPoints();
            player1.setPoints(points1+1);
            int points2 = player2.getPoints();
            player2.setPoints(points2+1);
            player1.draw();
            player2.draw();
        }
        else{
            int points = player2.getPoints();
            player2.setPoints(points+3);
            player1.loss();
            player2.win();
        }
        System.out.println(player1.getName() + " vs " + player2.getName() + "       " +player1Value + ":" + player2Value);




    }
}
