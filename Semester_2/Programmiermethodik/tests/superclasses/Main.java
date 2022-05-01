package tests.superclasses;

public class Main {
    public static void main(String[] args) {
        Employee employee = new Employee(15, "hans", 1);
        Manager manager = new Manager(15, "peter", 1);

        employee.foo();
        manager.foo();
    }
}
