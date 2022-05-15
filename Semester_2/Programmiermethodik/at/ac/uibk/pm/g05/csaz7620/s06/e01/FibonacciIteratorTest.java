package at.ac.uibk.pm.g05.csaz7620.s06.e01;


import org.junit.jupiter.api.Assertions;
import org.testng.annotations.Test;

import static org.junit.jupiter.api.Assertions.*;

public class FibonacciIteratorTest {

    @Test
    public void FibonacciTest(){
        FibonacciIterator x = new FibonacciIterator(10);
        assertEquals(x.curVal,1);
        x.next();
        assertEquals(x.curVal,1);
        x.next();
        assertEquals(x.curVal,2);
        x.next();
        assertEquals(x.curVal,3);
        x.next();
        assertEquals(x.curVal,5);
    }

    @Test
    public void ConstructorTest(){
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            FibonacciIterator x = new FibonacciIterator(-1);
        });
        String expectedMessage = "You need a value bigger then 0!";
        String exceptionMessage = exception.getMessage();
        Assertions.assertEquals(expectedMessage, exceptionMessage);
    }

    @Test
    public void nextTest(){
        FibonacciIterator x = new FibonacciIterator(2);
        x.next();
        x.next();
        Exception exception = assertThrows(IndexOutOfBoundsException.class, () -> {
            x.next();
        });
        String expectedMessage = "This fibonacci Iterator can only create values to the index " + 2;
        String exceptionMessage = exception.getMessage();
        Assertions.assertEquals(expectedMessage, exceptionMessage);
    }
}