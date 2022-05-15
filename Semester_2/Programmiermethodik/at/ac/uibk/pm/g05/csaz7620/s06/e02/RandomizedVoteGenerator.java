package at.ac.uibk.pm.g05.csaz7620.s06.e02;

import java.util.ArrayList;
import java.util.Random;

public class RandomizedVoteGenerator {
    private ArrayList<ElectoralRegion> electoralRegions;
    private ArrayList<PoliticalParty> politicalParties;

    public RandomizedVoteGenerator(ArrayList<ElectoralRegion> electoralRegions, ArrayList<PoliticalParty> politicalParties) {
        this.electoralRegions = electoralRegions;
        this.politicalParties = politicalParties;
    }

    public void voteRandom() throws WrongVoteException {
        VoteGenerator voteGenerator = new VoteGenerator();
        for (PoliticalParty politicalParty: politicalParties) {
            for(ElectoralRegion electoralRegion: electoralRegions){
                Random random = new Random();
                int upperBound = 100001;
                int j = random.nextInt(upperBound);
                for(int i = 0; i < j; i++){
                    voteGenerator.doVote(electoralRegions,politicalParties,electoralRegion,politicalParty);
                }
            }
        }
    }
}
