package at.ac.uibk.pm.g05.csaz7620.s03.e02;

public class CelsiusThermometer extends Thermometer {

    public CelsiusThermometer(int degree) {
        setDegreeCelsius(degree);
    }

    @Override
    public void printTemperature() {
        System.out.printf("%6.1f °C%n", getDegreeCelsius());
    }
}
