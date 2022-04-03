package at.ac.uibk.pm.g05.csaz7620.s03.e02;

public class KelvinThermometer extends Thermometer {

    public KelvinThermometer(int degree) {
        setDegreeKelvin(degree);
    }


    @Override
    public void printTemperature() {
        System.out.printf("%6.1f °K%n", getDegreeKelvin());
    }
}
