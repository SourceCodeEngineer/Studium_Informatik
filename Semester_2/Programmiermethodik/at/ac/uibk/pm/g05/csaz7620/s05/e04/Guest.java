package at.ac.uibk.pm.g05.csaz7620.s05.e04;

import java.util.ArrayList;
import java.util.Objects;

public class Guest extends Person {
    private String drink;
    private int amountOfDrink;
    private Bar bar;

    public Guest(String name) {
        super(name);
    }
    public void enterBar(Bar bar) throws AlreadyInTheBarException, BarAlreadyFullException {
        if(this.bar == bar){
            throw new AlreadyInTheBarException("You are already in this bar");
        }
        this.bar = bar;
        Guest guest = new Guest(name);
        bar.joinBar(guest);
    }
    public void leaveBar() throws NotInABarException {
        if(this.bar == null){
            throw new NotInABarException("You are not in a bar");
        }
        bar.leaveBar(bar.getGuestWithName(name));
        this.bar = null;
    }

    public void buyDrink(String drink, int amount) throws WrongAmountOfDrinksException, DrinkNotInMenuException {
        bar.getBarkeeper().serveDrink(drink, amount);
        this.drink = drink;
        this.amountOfDrink = amount;

    }

    public void consumeDrink() throws WrongAmountOfDrinksException {
        if(amountOfDrink > 0){
            System.out.println("Drinking...");
            amountOfDrink = amountOfDrink -1;
        }
        else{
            throw new WrongAmountOfDrinksException("You dont have a drink, order one!");
        }
    }

    public String getName() {
        return name;
    }

    public int getAmountOfDrink() {
        return amountOfDrink;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Guest guest = (Guest) o;
        return Objects.equals(name, guest.name);
    }
}
