package at.ac.uibk.pm.g05.csaz7620.s05.e04;

import java.util.ArrayList;

public class Bar {

    private String name;
    private Barkeeper barkeeper;
    private ArrayList<Guest> guests;
    private int maxAmountOfGuests;
    private int currentAmountOfGuests;

    public Bar(String name, Barkeeper barkeeper, ArrayList<Guest> guests, int maxAmountOfGuests) {
        this.name = name;
        this.barkeeper = barkeeper;
        this.guests = guests;
        this.maxAmountOfGuests = maxAmountOfGuests;
        this.currentAmountOfGuests = guests.size();
    }


    public void leaveBar(Guest guest) {
        try {
            guests.remove(guest);
            this.currentAmountOfGuests = currentAmountOfGuests - 1;
        } catch (NullPointerException e) {
            throw new IllegalArgumentException("Guest is not in the Bar");
        }
    }

    public void joinBar(Guest guest) throws BarAlreadyFullException {
        if (currentAmountOfGuests == maxAmountOfGuests) {
            throw new BarAlreadyFullException("Bar is full");
        } else {
            guests.add(guest);
            this.currentAmountOfGuests = currentAmountOfGuests + 1;

        }
    }

    public Barkeeper getBarkeeper() {
        return barkeeper;
    }

    public ArrayList<Guest> getGuests() {
        return guests;
    }

    public Guest getGuestWithName(String name){
        for (int i = 0; i < guests.size();i++){
            if(guests.get(i).getName().equals(name)){
                return guests.get(i);
            }
        }
        System.out.println("Not in the Bar");
        return null;
    }


    public int getCurrentAmountOfGuests(){
        return currentAmountOfGuests;
    }

    public int getMaxAmountOfGuests() {
        return maxAmountOfGuests;
    }
}
