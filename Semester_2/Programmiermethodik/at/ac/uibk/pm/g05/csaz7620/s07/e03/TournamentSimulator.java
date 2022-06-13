package e03;

import e02.ExampleGame;
import e02.Group;
import e02.Players;
import e02.RandomGroupGenerator;

import java.util.ArrayList;

public class TournamentSimulator {
        public static void main(String[] args) {
            System.out.println("Ausgabe aus der main()-Methode");
            ArrayList<Players> players = new ArrayList<>();
            ArrayList<Group> groups = new ArrayList<>();

            Players player = new Players("tobi");
            Players player1 = new Players("dani");
            Players player2 = new Players("anna");
            Players player3 = new Players("michi");
            Players player4 = new Players("jonas");
            Players player5 = new Players("steve");
            Players player6 = new Players("niklas");
            Players player7 = new Players("sarah");
            Players player8 = new Players("hirs");
            Players player9 = new Players("killian");
            Group group1 = new Group("Group 1");
            Group group2 = new Group("Group 2");

            players.add(player);
            players.add(player1);
            players.add(player2);
            players.add(player3);
            players.add(player4);
            players.add(player5);
            players.add(player6);
            players.add(player7);
            players.add(player8);
            players.add(player9);

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

            Group winnerGroup = new Group("winnerGroup");
            ArrayList<Players> winnerGroup1 = group1.getWinner();
            ArrayList<Players> winnerGroup2 = group2.getWinner();

            for (Players x: winnerGroup1) {
                x.setPoints(0);
                winnerGroup.add(x);
            }
            for (Players x: winnerGroup2) {
                x.setPoints(0);
                winnerGroup.add(x);
            }
            System.out.println("-----------------------------------");
            System.out.println("The final group: ");
            for (Players x: winnerGroup.getPlayers()) {
                System.out.print("[" + x.getName() +"]  ");
            }
            System.out.println();
            winnerGroup.playEncounters(exampleGame);
            System.out.println();
            winnerGroup.printRankingList();
            System.out.println();
            ArrayList<Players> winner = winnerGroup.getWinner();
            if(winner.size() == 1){
                System.out.println("The winner is " + winner.get(0).getName());
            }
            else{
                System.out.println("The winners are: ");
                for (Players x: winner) {
                    System.out.print(x.getName() + " ");
                }
            }
        }
    }

