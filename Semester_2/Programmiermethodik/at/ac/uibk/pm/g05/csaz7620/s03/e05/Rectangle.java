package at.ac.uibk.pm.g05.csaz7620.s03.e05;

public class Rectangle {
    private double length;
    private double height;

    public double getCircumference(double length, double height){
        return (length * 2) + (height * 2);
    }

    public double getArea(double length, double height){
        return length * height;
    }

    public double getLength() {
        return length;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }
}
