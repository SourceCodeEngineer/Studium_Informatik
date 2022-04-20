package at.ac.uibk.pm.g05.csaz7620.s04.e02;

import java.util.ArrayList;
import java.util.List;

public class Course {

    private List<String> students = new ArrayList<>();
    private static final int MAX_STUDENTS = 2;

    public void addStudent(String student) throws CourseFullException, StudentAlreadyEnrolledException {
        if (students.size() >= MAX_STUDENTS) {
            throw new CourseFullException("Course is already full!");
        }
        if (students.contains(student)) {
            throw new StudentAlreadyEnrolledException("Student is already enrolled!");
        }
        students.add(student);
    }
}
