package at.ac.uibk.pm.g05.csaz7620.s07.e02;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Group {
    private ArrayList<Players> players = new ArrayList<Players>();
    private String name;

    public Group(String name) {
        this.name = name;
    }

    public void add(Players player){
        players.add(player);
    }

    @Override
    public String toString() {
        return "Group{" +
                "players=" + players +
                ", name='" + name + '\'' +
                '}';
    }

    public void playEncounters(Game game){
        for(int i = 0; i < players.size();i++) {
            for (int j = i+1; j < players.size(); j++) {
                encounter(players.get(i), players.get(j),game);
            }
        }
    }

    private void encounter(Players player1, Players player2, Game game){
        RandomResultGenerator randomResultGenerator = new RandomResultGenerator(game);
        randomResultGenerator.generateResults(player1,player2);
    }

    public void printRankingList(){
        sortRanked();
        for (Players x:players) {
            System.out.println(getRanked(x) + ". " + x.getName() + ": " + x.getPoints() + " Points " + "Ecounter: " + (x.getWins()+x.getDraws()+x.getLosses())+ ": "+ x.getWins() + "/" + x.getDraws() + "/" + x.getLosses() + " w/d/l");
        }
    }

    public void sortRanked(){
        Collections.sort(players, new Comparator<Players>() {
            @Override
            public int compare(Players first, Players second) {
                if (first.getPoints() < second.getPoints()) {
                    return 1;
                }
                if (first.getPoints() > second.getPoints()) {
                    return -1;
                }
                return 0;
            }
        });
    }
    public int getRanked(Players player){
        int ranked = 1;
        for (int i = 0; i < players.size(); i++){
            if(player.getPoints() < players.get(i).getPoints()){
                ++ranked;
            }
        }
        return ranked;
    }

    public ArrayList<Players> getWinner(){
        Players currentWinner = players.get(0);
        ArrayList<Players> winner = new ArrayList<>();
        for(int i = 1; i < players.size();i++){
            if(players.get(i).getPoints() > currentWinner.getPoints()){
                currentWinner = players.get(i);
            }
        }
        for (Players x : players) {
            if(x.getPoints() == currentWinner.getPoints()){
                winner.add(x);
            }
        }
        return winner;
    }

    public ArrayList<Players> getPlayers() {
        return players;
    }
}