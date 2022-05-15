package e02;

import java.util.ArrayList;

public class VoteGenerator {

    public void doVote(ArrayList<ElectoralRegion> electoralRegions, ArrayList<PoliticalParty>politicalParties, ElectoralRegion electoralRegion, PoliticalParty politicalParty) throws WrongVoteException {
        if (!electoralRegions.contains(electoralRegion) || !politicalParties.contains(politicalParty)) {
            throw new WrongVoteException("InvalidVote");
        }
        politicalParty.getVote(electoralRegion);
    }
}
