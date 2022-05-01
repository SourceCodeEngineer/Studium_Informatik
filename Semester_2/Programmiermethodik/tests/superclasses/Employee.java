package tests.superclasses;

public class Employee {
    int id;
    String name;
    int permissions;

    public void foo(){
        System.out.println("foo super");
    }

    public Employee(int id, String name, int permissions) {
        this.id = id;
        this.name = name;
        this.permissions = permissions;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPermissions() {
        return permissions;
    }

    public void setPermissions(int permissions) {
        this.permissions = permissions;
    }
}
