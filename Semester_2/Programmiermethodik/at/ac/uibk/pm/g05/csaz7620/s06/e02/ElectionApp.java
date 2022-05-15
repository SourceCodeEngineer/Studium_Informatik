package e02;

import java.util.ArrayList;
import java.util.HashMap;

public class ElectionApp {
    public static void main(String[] args) throws WrongVoteException {

        System.out.println("Ausgabe aus der main()-Methode");
        ElectoralRegion electoralRegion = new ElectoralRegion("Pinzgau",5);
        ElectoralRegion electoralRegion1 = new ElectoralRegion("Hollersbach",5);
        ElectoralRegion electoralRegion2 = new ElectoralRegion("Innsbruck",5);
        ElectoralRegion electoralRegion3 = new ElectoralRegion("Salzburg",5);

        HashMap<ElectoralRegion,Integer> initVotes = new HashMap<>();
        initVotes.put(electoralRegion,0);
        initVotes.put(electoralRegion1,0);
        initVotes.put(electoralRegion2,0);
        initVotes.put(electoralRegion3,0);

        PoliticalParty politicalParty = new PoliticalParty("Tobi for die Präsident",initVotes);
        PoliticalParty politicalParty1 = new PoliticalParty("Bier",initVotes);
        PoliticalParty politicalParty2 = new PoliticalParty("Kaffee",initVotes);
        PoliticalParty politicalParty3 = new PoliticalParty("Red Bull",initVotes);

        ArrayList<PoliticalParty> politicalParties = new ArrayList<>();
        politicalParties.add(politicalParty);
        politicalParties.add(politicalParty1);
        politicalParties.add(politicalParty2);
        politicalParties.add(politicalParty3);

        ArrayList<ElectoralRegion> electoralRegions = new ArrayList<>();
        electoralRegions.add(electoralRegion);
        electoralRegions.add(electoralRegion1);
        electoralRegions.add(electoralRegion2);
        electoralRegions.add(electoralRegion3);


        ElectionSystem electionSystem = new ElectionSystem(electoralRegions,politicalParties);
        System.out.println(electionSystem);
        electionSystem.randomVote();
        System.out.println();
        System.out.println(electionSystem);



    }
}
