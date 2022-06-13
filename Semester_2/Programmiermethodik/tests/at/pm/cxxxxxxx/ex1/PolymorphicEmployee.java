package tests.at.pm.cxxxxxxx.ex1;

public abstract class PolymorphicEmployee {

    private String name;
    private final double hourlyRate;
    private final int weeklyHours;
    public final static double PUBLIC_TRANSPORTATION_BONUS = 20;

    protected PolymorphicEmployee(String name, int weeklyHours, double hourlyRate) {
        this.name = name;
        this.weeklyHours = weeklyHours;
        this.hourlyRate = hourlyRate;
    }

    public double getHourlyRate() {
        return hourlyRate;
    }

    public int getWeeklyHours() {
        return weeklyHours;
    }

    @Override
    public String toString() {
        return name + ", Weekly Salary: " + getSalary() + " EUR, Employee type: ";
    }

    public abstract double getSalary();

}
