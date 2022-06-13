package e01;

import com.google.common.collect.Ordering;
import org.junit.Test;
import org.junit.jupiter.api.Assertions;

import java.util.Comparator;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.*;

public class UserDatabaseTest {

    @Test
    public void saveUserTest() throws PrimaryKeyAlreadyInUseException {
        User user = new User("WhyAmICoding","Tobias","Griesser");
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        assertEquals(inMemoryDatabase.getSize(),0);
        inMemoryDatabase.save(user);
        assertEquals(inMemoryDatabase.getSize(),1);

        assertEquals(inMemoryDatabase.getDatabase().contains(user),true);
    }

    @Test
    public void saveUserExceptionTest() throws PrimaryKeyAlreadyInUseException {
        User user = new User("WhyAmICoding","Tobias","Griesser");
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(user);

        Exception exception = assertThrows(PrimaryKeyAlreadyInUseException.class, () -> {
            inMemoryDatabase.save(user);
        });
        String expectedMessage = "This primary key is already in use: " + "WhyAmICoding";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage,exceptionMessage);
        assertEquals(inMemoryDatabase.getSize(),1);
    }

    @Test
    public void deleteUserTest() throws PrimaryKeyAlreadyInUseException, EntityNotInDatabaseException {
        User user = new User("WhyAmICoding","Tobias","Griesser");
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(user);

        int size = inMemoryDatabase.getSize();
        assertEquals(size,1);
        inMemoryDatabase.delete(user);
        size = inMemoryDatabase.getSize();
        assertEquals(size,0);
        assertFalse(inMemoryDatabase.getDatabase().contains(user));
    }

    @Test
    public void deleteUserExceptionTest() throws PrimaryKeyAlreadyInUseException, EntityNotInDatabaseException {
        User user = new User("WhyAmICoding","Tobias","Griesser");
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(user);

        inMemoryDatabase.delete(user);
        Exception exception = assertThrows(EntityNotInDatabaseException.class, () -> {
            inMemoryDatabase.delete(user);
        });
        String expectedMessage = "This Object does not exist";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage,exceptionMessage);
    }
    @Test
    public void findOneTest() throws PrimaryKeyAlreadyInUseException {
        User user = new User("WhyAmICoding","Tobias","Griesser");
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(user);

        User user2 = new User("Moin","Steve","Jobless");
        inMemoryDatabase.save(user2);

        assertEquals(inMemoryDatabase.findeOne("WhyAmICoding").get(),user);
        assertEquals(inMemoryDatabase.findeOne("Moin").get(),user2);
        assertTrue(inMemoryDatabase.findeOne("ah").isEmpty());

    }
    @Test
    public void findAllTest() throws PrimaryKeyAlreadyInUseException {
        User user = new User("WhyAmICoding","Tobias","Griesser");
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(user);

        User user2 = new User("Moin","Steve","Jobless");
        inMemoryDatabase.save(user2);

        assertTrue(inMemoryDatabase.getDatabase().get(0).equals(user));
        inMemoryDatabase.findAll(Ordering.usingToString());   //alphabetical sorting
        assertTrue(inMemoryDatabase.getDatabase().get(0).equals(user2));
    }

}