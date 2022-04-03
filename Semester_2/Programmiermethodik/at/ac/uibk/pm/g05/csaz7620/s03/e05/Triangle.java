package at.ac.uibk.pm.g05.csaz7620.s03.e05;

public class Triangle {
    private double side1;
    private double side2;
    private double side3;

    public double getCircumference(double side1, double side2, double side3){
        return side1 + side2 + side3;
    }

    public double getArea(double side1, double side2, double side3){
        double p = (side1 + side2 + side3) /2;
        return Math.sqrt((p * (p-side1) * (p - side2) * (p-side3)));
    }

    public double getSide1() {
        return side1;
    }

    public void setSide1(double side1) {
        this.side1 = side1;
    }

    public double getSide2() {
        return side2;
    }

    public void setSide2(double side2) {
        this.side2 = side2;
    }

    public double getSide3() {
        return side3;
    }

    public void setSide3(double side3) {
        this.side3 = side3;
    }
}
