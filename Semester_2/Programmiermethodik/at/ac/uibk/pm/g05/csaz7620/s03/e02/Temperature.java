package at.ac.uibk.pm.g05.csaz7620.s03.e02;

public class Temperature {
    private static final double ABSOLUTE_ZERO_CELSIUS = -273.15;

    private Temperature() {
    }

    public static double celsiusToFahrenheit(double degreeCelsius) {
        return degreeCelsius * 9.0 / 5.0 + 32;
    }

    public static double fahrenheitToCelsius(double degreeFahrenheit) {
        return (degreeFahrenheit - 32) * 5.0 / 9.0;
    }

    public static double celsiusToKelvin(double degreeCelsius) {
        return degreeCelsius - ABSOLUTE_ZERO_CELSIUS;
    }

    public static double kelvinToCelsius(double degreeKelvin) {
        return degreeKelvin + ABSOLUTE_ZERO_CELSIUS;
    }

    public static double kelvinToFahrenheit(double degreeKelvin) {
        double degreeCelsius = kelvinToCelsius(degreeKelvin);
        return celsiusToFahrenheit(degreeCelsius);
    }

    public static double fahrenheitToKelvin(double degreeFahrenheit) {
        double degreeCelsius = fahrenheitToCelsius(degreeFahrenheit);
        return celsiusToKelvin(degreeCelsius);
    }

}
