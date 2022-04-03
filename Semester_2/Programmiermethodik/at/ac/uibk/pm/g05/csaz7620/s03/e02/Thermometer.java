package at.ac.uibk.pm.g05.csaz7620.s03.e02;

public abstract class Thermometer {
    public double degree;

    public final double getDegreeCelsius() {
        return Temperature.kelvinToCelsius(degree);
    }

    public final double getDegreeFahrenheit() {
        return Temperature.kelvinToFahrenheit(degree);
    }

    public final double getDegreeKelvin() {
        return degree;
    }

    public final void setDegreeCelsius(double degreeCelsius) {
        this.degree = Temperature.celsiusToKelvin(degreeCelsius);
    }

    public final void setDegreeFahrenheit(double degreeFahrenheit) {
        this.degree = Temperature.fahrenheitToKelvin(degreeFahrenheit);
    }

    public final void setDegreeKelvin(double degree) {
        this.degree = degree;
    }

    public abstract void printTemperature();
}
