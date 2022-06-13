package e02;

import e01.Entity;

import java.util.ArrayList;

public class TournamentManager {

    public static void main(String[] args) {
        System.out.println("Ausgabe aus der main()-Methode");
        ArrayList<Players> players = new ArrayList<>();
        ArrayList<Group> groups = new ArrayList<>();

        Players player = new Players("tobi");
        Players player1 = new Players("dani");
        Players player2 = new Players("anna");
        Players player3 = new Players("michi");
        Players player4 = new Players("jonas");
        Group group1 = new Group("Group 1");
        Group group2 = new Group("Group 2");

        players.add(player);
        players.add(player1);
        players.add(player2);
        players.add(player3);
        players.add(player4);

        groups.add(group1);
        groups.add(group2);


        RandomGroupGenerator randomGroupGenerator = new RandomGroupGenerator();
        randomGroupGenerator.generateGroups(players,groups);
        ExampleGame exampleGame = new ExampleGame();

        for (Group x:groups) {
            System.out.println();
            x.playEncounters(exampleGame);
        }
        for (Group x:groups) {
            System.out.println();
            x.printRankingList();
        }
    }



}
