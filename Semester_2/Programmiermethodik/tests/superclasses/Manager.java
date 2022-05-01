package tests.superclasses;

public class Manager extends Employee{

    String badge;

    public Manager(int id, String name, int permissions) {
        super(id, name, permissions);
    }

    public String getBadge() {
        return badge;
    }

    public void setBadge(String badge) {
        this.badge = badge;
    }

    @Override
    public void foo(){
        // super.foo(); for super class
        System.out.println("subclass");
    }
}
