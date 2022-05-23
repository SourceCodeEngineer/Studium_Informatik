package at.ac.uibk.pm.g05.csaz7620.s07.e02;

import java.util.ArrayList;
import java.util.Random;

public class RandomGroupGenerator {

    public void generateGroups(ArrayList<Players> players, ArrayList<Group> groups) {
        int playersPerTeam = players.size()/groups.size();

        GroupGenerator groupGenerator = new GroupGenerator();
        for (int i = 0; i < groups.size(); i++) {
            int n = 0;
            while(n < playersPerTeam) {
                Random rand = new Random();
                if(players.size() > 0) {
                    int random = rand.nextInt(players.size());
                    groupGenerator.addToGroup(players.get(random), groups.get(i));
                    players.remove(random);
                }
                n++;
            }
        }
        if(!players.isEmpty()){
            groupGenerator.addToGroup(players.get(0),groups.get(groups.size()-1));
        }
    }
}

