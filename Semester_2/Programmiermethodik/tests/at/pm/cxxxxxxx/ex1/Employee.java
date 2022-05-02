package at.pm.cxxxxxxx.ex1;

public class Employee {

    private String name;
    private final String type;
    private double hourlyRate;
    private static final double publicTransportationBonus = 20;

    public Employee(String name, String type) throws Exception {
        this.name = name;
        this.type = type;

        switch (this.type) {
            case EmployeeType.STUDENT:
                this.hourlyRate = 18.2;
                break;
            case EmployeeType.ADMINISTRATIVE:
                this.hourlyRate = 36.4;
                break;
            case EmployeeType.PROFESSOR:
                this.hourlyRate = 95.2;
                break;
            default:
                throw new Exception("Invalid employee type: " + type);
        }
    }

    public double getSalary() {
        double salary = 0;
        switch (type) {
            case EmployeeType.STUDENT:
                salary = hourlyRate * 20 + publicTransportationBonus * 0.5;
                break;
            case EmployeeType.ADMINISTRATIVE:
                salary = hourlyRate * 30 + publicTransportationBonus * 0.75;
                break;
            case EmployeeType.PROFESSOR:
                salary = hourlyRate * 40;
                break;
        }
        return salary;

    }

    @Override
    public String toString() {
        return name + ", Weekly Salary: " + getSalary() + " EUR, " + "Employee type: " + type;
    }

}