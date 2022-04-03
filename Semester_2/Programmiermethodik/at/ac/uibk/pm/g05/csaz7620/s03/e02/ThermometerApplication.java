package at.ac.uibk.pm.g05.csaz7620.s03.e02;

public class ThermometerApplication {

    public static void main(String[] args) {
        Thermometer celsius = new CelsiusThermometer(10);
        celsius.printTemperature();
        celsius.degree = 20;
        celsius.printTemperature();
    }
}