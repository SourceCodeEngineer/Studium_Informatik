package at.ac.uibk.pm.g05.csaz7620.s04.e03;

import java.util.Date;

public class User {
    private String firstName;
    private String lastName;
    private Date birthDate;

    public User(String firstName, String lastName, Date birthDate) throws IllegalArgumentException {
        if (firstName == null || lastName == null || firstName.isEmpty() || lastName.isEmpty()){
            throw new IllegalArgumentException("Invalid User parameters!");
        }
        else {
            this.firstName = firstName;
            this.lastName = lastName;
            this.birthDate = birthDate;
        }
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public Date getBirthDate() {
        return birthDate;
    }

}

