package week6;

import java.text.MessageFormat;
import java.util.Comparator;
import java.util.PriorityQueue;

public class FlightManagement {

    private static final String LOGGING_MESSAGE =
            "Expected plane: {0}, actual plane: {1}";
    private PriorityQueue<IncomingPlane> arrivingPlanes;

    public FlightManagement(Comparator<IncomingPlane> comparator) {
        arrivingPlanes = new PriorityQueue(comparator);
    }

    public void registerPlane(IncomingPlane incomingPlane) {
        arrivingPlanes.add(incomingPlane);
    }

    public IncomingPlane getNextPlane() {
        return arrivingPlanes.poll();
    }

    public static void main(String[] args) {
        FlightManagement flightManagement =
                new FlightManagement(new PlanePriorityComparator());

        // Priority for plane with critical fuel status
        IncomingPlane planeA = new IncomingPlane("A", 26, 10);
        IncomingPlane planeB = new IncomingPlane("B", 24, -10);
        flightManagement.registerPlane(planeA);
        flightManagement.registerPlane(planeB);
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "B",
                flightManagement.getNextPlane()
                        .getIdentifier()));
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "A",
                flightManagement.getNextPlane()
                        .getIdentifier()));

        // Priority for plane with higher delay
        IncomingPlane planeC = new IncomingPlane("C", 34, 10);
        IncomingPlane planeD = new IncomingPlane("D", 30, -10);
        flightManagement.registerPlane(planeC);
        flightManagement.registerPlane(planeD);
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "C",
                flightManagement.getNextPlane()
                        .getIdentifier()));
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "D",
                flightManagement.getNextPlane()
                        .getIdentifier()));

        // Priority for plane with less fuel
        IncomingPlane planeE = new IncomingPlane("E", 60, 50);
        IncomingPlane planeF = new IncomingPlane("F", 30, 10);
        flightManagement.registerPlane(planeE);
        flightManagement.registerPlane(planeF);
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "E",
                flightManagement.getNextPlane()
                        .getIdentifier()));
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "F",
                flightManagement.getNextPlane()
                        .getIdentifier()));

        // Priority for plane with less fuel
        IncomingPlane planeG = new IncomingPlane("G", 12, 100);
        IncomingPlane planeH = new IncomingPlane("H", 10, 100);
        flightManagement.registerPlane(planeG);
        flightManagement.registerPlane(planeH);
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "H",
                flightManagement.getNextPlane()
                        .getIdentifier()));
        System.out.println(MessageFormat.format(LOGGING_MESSAGE, "G",
                flightManagement.getNextPlane()
                        .getIdentifier()));
    }

}

class PlanePriorityComparator implements Comparator<IncomingPlane> {

    @Override
    public int compare(IncomingPlane o1, IncomingPlane o2) {
        // planes have less than 25 % fuel?
        if (o1.getRemainingFuel() < 25 || o2.getRemainingFuel() < 25){
            // both planes have critical fuel!
            if (o1.getRemainingFuel() < o2.getRemainingFuel()){
                return -1;
            } else {
                return 1;
            }

        } else {
            // check for delay because we have enough fuel!

            if (o1.getDelay() > 0 || o2.getDelay() > 0){
                // delay is for at least 1 plane poitive!
                if (o1.getDelay() > o2.getDelay()){
                    return -1;
                } else {
                    return 1;
                }

            } else {
                // both are arriving early!
                if (o1.getRemainingFuel() < o2.getRemainingFuel()){
                    return -1;
                } else {
                    return 1;
                }
            }
        }
    }
}


class IncomingPlane {

    private final String identifier;

    // Remaining fuel in percent
    private final int remainingFuel;

    // Delay in minutes
    private final int delay;

    public IncomingPlane(String identifier, int remainingFuel, int delay) {
        this.identifier = identifier;
        this.remainingFuel = remainingFuel;
        this.delay = delay;
    }

    public String getIdentifier() {
        return identifier;
    }

    public int getRemainingFuel() {
        return remainingFuel;
    }

    public int getDelay() {
        return delay;
    }
}

