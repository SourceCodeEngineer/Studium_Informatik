package at.ac.uibk.pm.g05.csaz7620.s07.e01;

public class User extends Entity{

    private String username;
    private String name;
    private String surname;

    public User(String username, String name, String surname ) {
        super(name + " " + surname, username);
    }
}
