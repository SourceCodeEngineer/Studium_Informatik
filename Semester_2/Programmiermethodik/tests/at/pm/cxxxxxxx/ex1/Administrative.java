package at.pm.cxxxxxxx.ex1;

public class Administrative extends PolymorphicEmployee {

    private final static double DEFAULT_HOURLY_RATE = 36.4;
    private final static int DEFAULT_WEEKLY_HOURS = 30;

    public Administrative(String name) {
        super(name, DEFAULT_WEEKLY_HOURS, DEFAULT_HOURLY_RATE);
    }

    @Override
    public String toString() {
        return super.toString() + "ADMINISTRATIVE";
    }

    @Override
    public double getSalary() {
        return getHourlyRate() * getWeeklyHours() + PUBLIC_TRANSPORTATION_BONUS * 0.75;
    }

}
