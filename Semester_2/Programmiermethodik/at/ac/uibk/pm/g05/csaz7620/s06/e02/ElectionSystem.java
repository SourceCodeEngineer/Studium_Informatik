package e02;

import java.util.ArrayList;
import java.util.HashMap;

public class ElectionSystem {
    private ArrayList<ElectoralRegion> electoralRegions = new ArrayList<>();
    private ArrayList<PoliticalParty> politicalParties = new ArrayList<>();

    public ElectionSystem(ArrayList<ElectoralRegion> electoralRegions, ArrayList<PoliticalParty> politicalParties) {
        this.electoralRegions = electoralRegions;
        this.politicalParties = politicalParties;
    }

    public void vote(ElectoralRegion electoralRegion, PoliticalParty politicalParty) throws WrongVoteException {
        VoteGenerator voteGenerator = new VoteGenerator();
        voteGenerator.doVote(electoralRegions, politicalParties, electoralRegion, politicalParty);
    }

    public void randomVote() throws WrongVoteException {
        RandomizedVoteGenerator randomizedVoteGenerator = new RandomizedVoteGenerator(electoralRegions,politicalParties);
        randomizedVoteGenerator.voteRandom();
    }

    @Override
    public String toString() {
        return "ElectionSystem{" +
                "electoralRegions=" + electoralRegions.toString() +
                ", politicalParties=" + politicalParties.toString() +
                '}';
    }
}
