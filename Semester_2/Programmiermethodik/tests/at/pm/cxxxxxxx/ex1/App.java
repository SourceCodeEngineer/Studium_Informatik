package tests.at.pm.cxxxxxxx.ex1;

public class App {
    public static void main(String[] args) {

        //make sure the output of printEmployees and printPolymorphicEmployees methods are identical
        printEmployees();
        printPolymorphicEmployees();

    }

    public static void printEmployees() {
        try {
            Employee professor = new Employee("Alexander Blaas", EmployeeType.PROFESSOR);
            Employee admin = new Employee("Umutcan Simsek", EmployeeType.ADMINISTRATIVE);
            Employee student = new Employee("Elwin Huaman", EmployeeType.STUDENT);

            System.out.println(professor);
            System.out.println(admin);
            System.out.println(student);
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public static void printPolymorphicEmployees() {
        // Uncomment the following code and initialize the variables as expected

        PolymorphicEmployee professor = new Professor("Alexander Blaas");
        PolymorphicEmployee admin = new Administrative("Umutcan Simsek");
        PolymorphicEmployee student = new Student("Elwin Huaman");

        System.out.println(professor);
        System.out.println(admin);
        System.out.println(student);
    }

}
