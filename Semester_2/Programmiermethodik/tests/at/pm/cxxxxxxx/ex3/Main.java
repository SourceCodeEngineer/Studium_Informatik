package at.pm.cxxxxxxx.ex3;

public class Main {

    public static void main(String[] args) {
        SortedList<String> stringList = new SortedList<>();
        stringList.addElement("a");
        stringList.addElement("a");
        stringList.addElement("z");
        stringList.addElement("b");

        SortedList<Integer> intList = new SortedList<>();
        intList.addElement(10);
        intList.addElement(0);
        intList.addElement(3);
        intList.addElement(3);

        System.out.printf("String-list:%n%s%n", stringList.getSorted());
        stringList.removeElement("a");
        System.out.println(stringList.getSorted());
        stringList.removeElement("a");
        System.out.println(stringList.getSorted());

        System.out.printf("%nInt-list:%n%s%n", intList.getSorted());
        intList.removeElement(3);
        System.out.println(intList.getSorted());
        intList.removeElement(3);
        System.out.println(intList.getSorted());
    }

}

