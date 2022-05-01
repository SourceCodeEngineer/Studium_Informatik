package at.ac.uibk.pm.g05.csaz7620.s03.e03;

public class Exercise3Application {
        public static void main(String[] args) {
                Top o1 = new Middle();
                Middle o2 = new Bottom();
                o1.m(o1);
                o1.m(o2);
                o2.m(o1);
                o2.m(o2);
        }
}
