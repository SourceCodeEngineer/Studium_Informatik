package at.ac.uibk.pm.g05.csaz7620.s03.e05;

public class Main {
    public static void main(String[] args) {
        Circle circle = new Circle();
        Rectangle rectangle = new Rectangle();
        Triangle triangle = new Triangle();

        circle.setRadius(5);
        System.out.println(circle.getCircumference(circle.getRadius()));
        System.out.println(circle.getArea(circle.getRadius()));

        rectangle.setHeight(10);
        rectangle.setLength(7);
        System.out.println(rectangle.getCircumference(rectangle.getLength(), rectangle.getHeight()));
        System.out.println(rectangle.getArea(rectangle.getLength(), rectangle.getHeight()));

        triangle.setSide1(7);
        triangle.setSide2(8);
        triangle.setSide3(9);
        System.out.println(triangle.getCircumference(triangle.getSide1(), triangle.getSide2(), triangle.getSide3()));
        System.out.println(triangle.getArea(triangle.getSide1(), triangle.getSide2(), triangle.getSide3()));
    }
}
