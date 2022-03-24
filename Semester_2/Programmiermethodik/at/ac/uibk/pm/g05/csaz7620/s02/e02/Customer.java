package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class Customer {
    private String name;
    private String surname;
    private Creditrating creditrating;

    public Customer(String name, String surname, Creditrating creditrating) {
        setName(name);
        setSurname(surname);
        setCreditrating(creditrating);
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

    public Creditrating getCreditrating() {
        return creditrating;
    }

    public void setCreditrating(Creditrating creditrating) {
        this.creditrating = creditrating;
    }
}
