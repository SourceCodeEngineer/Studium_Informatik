package at.pm.cxxxxxxx.ex1;

public class Student extends PolymorphicEmployee {

    private final static double DEFAULT_HOURLY_RATE = 18.2;
    private final static int DEFAULT_WEEKLY_HOURS = 20;

    public Student(String name) {
        super(name, DEFAULT_WEEKLY_HOURS, DEFAULT_HOURLY_RATE);
    }

    @Override
    public String toString() {
        return super.toString() + "STUDENT";
    }

    @Override
    public double getSalary() {
        return getHourlyRate() * getWeeklyHours() + PUBLIC_TRANSPORTATION_BONUS * 0.5;
    }

}
