package at.ac.uibk.pm.g05.csaz7620.s06.e02;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class PoliticalParty {
    private String name;
    private Map<ElectoralRegion,Integer> votesPerRegion = new HashMap<>();

    public PoliticalParty(String name, HashMap<ElectoralRegion,Integer> votesPerRegion ) {
        this.name = name;
        this.votesPerRegion = votesPerRegion;
    }

    public void getVote(ElectoralRegion electoralRegion){
        int votes = votesPerRegion.get(electoralRegion);
        int newVotes = votes + 1;
        votesPerRegion.replace(electoralRegion,votes,newVotes);
    }

    @Override
    public String toString() {
        return "\n"+name + " " + votesPerRegion;
    }
}
