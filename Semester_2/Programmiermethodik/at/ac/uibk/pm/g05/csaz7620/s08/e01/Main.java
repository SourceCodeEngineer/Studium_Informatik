package e01;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;

public class Main {
    public static void main(String[] args){
        ArrayList<Person> people = new ArrayList<>();
        Person tobi = new Person("Tobias","Griesser", new Date(2001, Calendar.AUGUST,4));
        Person anna = new Person("Anna","Winkler", new Date(2000,Calendar.DECEMBER,30));
        Person dani = new Person("Dani","Ensmann",new Date(2001,Calendar.APRIL,02));

        people.add(tobi);
        people.add(anna);
        people.add(dani);


        System.out.println("Unsorted: ");
        System.out.println(people);

        PersonManager personManager = new PersonManager(people);
        PersonManager.Sort sort = personManager.new Sort(people);

        sort.sortByFirstName();
        System.out.println("Sorted by FirstName: ");
        System.out.println(personManager);

        sort.sortByLastName();
        System.out.println("Sorted by LastName: ");
        System.out.println(personManager);

        sort.sortBirthday();
        System.out.println("Sorted by Birthday: ");
        System.out.println(personManager);
    }
}
