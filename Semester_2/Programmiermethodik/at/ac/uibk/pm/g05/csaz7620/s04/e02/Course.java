package at.ac.uibk.pm.g05.csaz7620.s04.e02;

import java.util.ArrayList;
import java.util.List;

public class Course {

    private List<String> students = new ArrayList<>();
    private static final int MAX_STUDENTS = 2;

    public boolean addStudent(String student) {
        if (students.size() >= MAX_STUDENTS) {
            return false;
        }
        if (students.contains(student)) {
            return false;
        }
        students.add(student);
        return true;
    }
}
