package at.ac.uibk.pm.g05.csaz7620.s05.e05;;

import at.ac.uibk.pm.g05.csaz7620.s05.e04.*;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class BarTest {

    @Test
    public void enterBarTest() throws AlreadyInTheBarException, BarAlreadyFullException {
        Barkeeper barkeeper = new Barkeeper("Steve");
        Bar bar = new Bar("Zappas",barkeeper,new ArrayList<>(),15);
        Guest tobi = new Guest("tobi");
        assertEquals(bar.getCurrentAmountOfGuests(),0);
        tobi.enterBar(bar);
        assertEquals(bar.getCurrentAmountOfGuests(),1);

        Exception exception = assertThrows(AlreadyInTheBarException.class, () -> {
            tobi.enterBar(bar);
        });
        String expectedMessage = "You are already in this bar";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);

        ArrayList<Guest> guests = new ArrayList<>();
        Guest franz = new Guest("Franz");
        guests.add(franz);
        Bar bar2 = new Bar("Irish",new Barkeeper("Nils"),guests,1);
        Exception exception2 = assertThrows(BarAlreadyFullException.class, () -> {
            tobi.enterBar(bar2);
        });
        String expectedMessage2 = "Bar is full";
        String exceptionMessage2 = exception2.getMessage();
        assertEquals(expectedMessage2, exceptionMessage2);

    }

    @Test
    public void leaveBarTest() throws BarAlreadyFullException, AlreadyInTheBarException, NotInABarException {
        Barkeeper barkeeper2 = new Barkeeper("Jon");
        Bar bar2 = new Bar("Mustache",barkeeper2,new ArrayList<>(),15);
        Guest phil = new Guest("phil");
        phil.enterBar(bar2);
        assertEquals(bar2.getCurrentAmountOfGuests(),1);
        phil.leaveBar();
        assertEquals(bar2.getCurrentAmountOfGuests(),0);

        Exception exception = assertThrows(NotInABarException.class, () -> {
            phil.leaveBar();
        });
        String expectedMessage = "You are not in a bar";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);

    }

    @Test
    public void orderTest() throws BarAlreadyFullException, AlreadyInTheBarException, WrongAmountOfDrinksException, DrinkNotInMenuException {
        Barkeeper barkeeper3 = new Barkeeper("Niko");
        Bar bar3 = new Bar("Mustache",barkeeper3,new ArrayList<>(),15);
        Guest nils = new Guest("nils");
        nils.enterBar(bar3);
        nils.buyDrink("beer",1);
        assertEquals(nils.getAmountOfDrink(),1);

        Exception exception = assertThrows(WrongAmountOfDrinksException.class, () -> {
            nils.buyDrink("beer",999999);
        });
        assertEquals(nils.getAmountOfDrink(),1);

        Exception exception2 = assertThrows(WrongAmountOfDrinksException.class, () -> {
            nils.buyDrink("beer",-1);
        });
        assertEquals(nils.getAmountOfDrink(),1);

        Exception exception3 = assertThrows(DrinkNotInMenuException.class, () -> {
            nils.buyDrink("lizard",1);
        });
        String expectedMessage = "Sorry we dont have this drink!";
        String exceptionMessage = exception3.getMessage();
        assertEquals(expectedMessage, exceptionMessage);
        assertEquals(nils.getAmountOfDrink(),1);

        Exception exception4 = assertThrows(DrinkNotInMenuException.class, () -> {
            nils.buyDrink("“ueicbksjdhd”",1);
        });
        String expectedMessage2 = "Sorry we dont have this drink!";
        String exceptionMessage2 = exception4.getMessage();
        assertEquals(expectedMessage2, exceptionMessage2);
        assertEquals(nils.getAmountOfDrink(),1);

    }

    @Test
    public void toStringTest(){
        Barkeeper barkeeper4 = new Barkeeper("Niko");
        String string = barkeeper4.toString();
        assertEquals(string,"The Barkeeper is called " + "Niko");
    }

    @Test
    public void consumeDrinkTest() throws BarAlreadyFullException, AlreadyInTheBarException, WrongAmountOfDrinksException, DrinkNotInMenuException {
        Barkeeper barkeeper4 = new Barkeeper("Niko");
        Bar bar4 = new Bar("Mustache",barkeeper4,new ArrayList<>(),15);
        Guest michael = new Guest("michael");
        michael.enterBar(bar4);
        michael.buyDrink("beer",2);
        assertEquals(michael.getAmountOfDrink(),2);
        michael.consumeDrink();
        assertEquals(michael.getAmountOfDrink(),1);
        michael.consumeDrink();
        assertEquals(michael.getAmountOfDrink(),0);

        Exception exception = assertThrows(WrongAmountOfDrinksException.class, () -> {
            michael.consumeDrink();
        });
        String expectedMessage = "You dont have a drink, order one!";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage, exceptionMessage);
    }
}

