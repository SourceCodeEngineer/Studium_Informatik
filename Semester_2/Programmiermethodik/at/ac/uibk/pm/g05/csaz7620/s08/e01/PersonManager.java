package e01;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;

public class PersonManager {
    private ArrayList<Person> people = new ArrayList<>();

    public PersonManager(ArrayList<Person> people) {
        this.people = people;
    }

    @Override
    public String toString() {
        return "PersonManager{" +
                "people=" + people +
                '}';
    }

    public class Sort{
        private ArrayList<Person> people = new ArrayList<>();

        public Sort(ArrayList<Person> people) {
            this.people = people;
        }

        public void sortByFirstName(){
            Collections.sort(people, (o1, o2) -> {
                String fn1 = o1.getFirstName();
                String fn2 = o2.getFirstName();
                int res = fn1.compareTo(fn2);
                return res;

            });
        }
        public void sortByLastName(){
            Collections.sort(people, (o1, o2) -> {
                String fn1 = o1.getLastName();
                String fn2 = o2.getLastName();
                int res = fn1.compareTo(fn2);
                return res;

            });
        }
        public void sortBirthday(){
            Collections.sort(people, (o1, o2) -> {
                Date fn1 = o1.getBirthday();
                Date fn2 = o2.getBirthday();
                int res = fn1.compareTo(fn2);
                return res;

            });
        }

    }
}
