package e01;

public class User extends Entity{

    private String username;
    private String name;
    private String surname;

    public User(String username, String name, String surname ) {
        super(name + " " + surname, username);
    }
}
