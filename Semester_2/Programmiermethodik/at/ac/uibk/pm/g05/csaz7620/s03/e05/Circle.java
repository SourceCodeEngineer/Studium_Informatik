package at.ac.uibk.pm.g05.csaz7620.s03.e05;

public class Circle {
    private double radius;

    public double getCircumference(double radius){
        return 2 * Math.PI * radius;
    }

    public double getArea(double radius){
        return radius * radius * Math.PI;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }
}
