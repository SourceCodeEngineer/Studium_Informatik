package at.pm.cxxxxxxx.ex1;

public class Professor extends PolymorphicEmployee {

    private final static double DEFAULT_HOURLY_RATE = 95.2;
    private final static int DEFAULT_WEEKLY_HOURS = 40;

    public Professor(String name) {
        super(name, DEFAULT_WEEKLY_HOURS, DEFAULT_HOURLY_RATE);
    }

    @Override
    public String toString() {
        return super.toString() + "PROFESSOR";
    }

    @Override
    public double getSalary() {
        return getHourlyRate() * getWeeklyHours();
    }

}
