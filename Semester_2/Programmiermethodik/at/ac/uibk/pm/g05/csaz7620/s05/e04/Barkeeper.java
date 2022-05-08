package at.ac.uibk.pm.g05.csaz7620.s05.e04;

import java.util.ArrayList;

public class Barkeeper extends Person {

    private Bar workingPlace;

    public Barkeeper(String name, Bar workingPlace) {
        super(name);
        this.workingPlace = workingPlace;
    }
    public Barkeeper(String name){
        super(name);
    }


    public void serveDrink(String drink, int amount) throws DrinkNotInMenuException, WrongAmountOfDrinksException {
        if (drink.equals("beer")) {
            Beer beer = new Beer();
            if(beer.checkAmount(amount)){
                System.out.println("Getting " + amount + " of beer");
                return;
            }
            else{
                throw new WrongAmountOfDrinksException("Sir, you need at least " + beer.getLowerLimit() + " and lesser then " + beer.getUpperLimit() + "beers");
            }
        }
        if (drink.equals("orangeJuice")) {
            OrangeJuice orangeJuice = new OrangeJuice();
            if(orangeJuice.checkAmount(amount)){
                System.out.println("Getting " + amount + " of beer");
                return;
            }
            else{
                throw new WrongAmountOfDrinksException("Sir, you need at least " + orangeJuice.getLowerLimit() + " and lesser then " + orangeJuice.getUpperLimit() + "orangeJuice");
            }

        } else {
            throw new DrinkNotInMenuException("Sorry we dont have this drink!");
        }
    }

    @Override
    public String toString() {
        return "The Barkeeper is called " + this.name;
    }

    public void setWorkingPlace(Bar workingPlace) {
        this.workingPlace = workingPlace;
    }

}
