package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class Customer {
    private String name;
    private String surname;
    private CreditRating creditrating;

    public Customer(String name, String surname, CreditRating creditrating) {
        setName(name);
        setSurname(surname);
        setCreditRating(creditrating);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public CreditRating getCreditRating() {
        return creditrating;
    }

    public void setCreditRating(CreditRating creditrating) {
        this.creditrating = creditrating;
    }
}
