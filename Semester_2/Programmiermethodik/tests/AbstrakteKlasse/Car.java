package tests.AbstrakteKlasse;

// other example: https://www.programiz.com/java-programming/abstract-classes-methods
public abstract class Car {
    int ps;
    int weight;
    String color; // could also be enum

    public double foo(int weight, int ps){
        return weight / ps;
    }

    public Car(int ps, int weight, String color) {
        this.ps = ps;
        this.weight = weight;
        this.color = color;
    }

    public int getPs() {
        return ps;
    }

    public void setPs(int ps) {
        this.ps = ps;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
