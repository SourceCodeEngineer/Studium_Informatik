package at.ac.uibk.pm.g05.csaz7620.s06.e02;

public class ElectoralRegion {
    private String name;
    private int maxNumberOfSeats;

    public ElectoralRegion(String name, int maxNumberOfSeats) {
        this.name = name;
        this.maxNumberOfSeats = maxNumberOfSeats;
    }

    @Override
    public String toString() {
        return name;
    }
}
