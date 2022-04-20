package at.ac.uibk.pm.g05.csaz7620.s04.e02;

public class CourseApplication {

    public static void main(String[] args) {
        Course course = new Course();
        String[] students = {"Donald Duck", "Donald Duck", "Uncle Scrooge", "Gyro Gearloose"};

        for (String student : students) {
            try {
                course.addStudent(student);
                System.out.println("Successfully added " + student);
            } catch (StudentAlreadyEnrolledException x) {
                x.printStackTrace();
                System.out.println("Failed to add " + student);
            } catch (CourseFullException x) {
                x.printStackTrace();
                System.out.println("Failed to add " + student);
            }
        }
    }
}
