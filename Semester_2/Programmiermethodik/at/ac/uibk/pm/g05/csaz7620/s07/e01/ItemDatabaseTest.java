package at.ac.uibk.pm.g05.csaz7620.s07.e01;

import com.google.common.collect.Ordering;
import org.testng.annotations.Test;

import static org.junit.jupiter.api.Assertions.*;

public class ItemDatabaseTest {

    @Test
    public void saveUserTest() throws PrimaryKeyAlreadyInUseException {
        Item item = new Item(12,"apple",50);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        assertEquals(inMemoryDatabase.getSize(),0);
        inMemoryDatabase.save(item);
        assertEquals(inMemoryDatabase.getSize(),1);

        assertEquals(inMemoryDatabase.getDatabase().contains(item),true);
    }

    @Test
    public void saveUserExceptionTest() throws PrimaryKeyAlreadyInUseException {
        Item item = new Item(12,"apple",50);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(item);

        Exception exception = assertThrows(PrimaryKeyAlreadyInUseException.class, () -> {
            inMemoryDatabase.save(item);
        });
        String expectedMessage = "This primary key is already in use: " + 12;
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage,exceptionMessage);
        assertEquals(inMemoryDatabase.getSize(),1);
    }

    @Test
    public void deleteUserTest() throws PrimaryKeyAlreadyInUseException, EntityNotInDatabaseException {
        Item item = new Item(12,"apple",50);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(item);

        int size = inMemoryDatabase.getSize();
        assertEquals(size,1);
        inMemoryDatabase.delete(item);
        size = inMemoryDatabase.getSize();
        assertEquals(size,0);
        assertFalse(inMemoryDatabase.getDatabase().contains(item));
    }

    @Test
    public void deleteUserExceptionTest() throws PrimaryKeyAlreadyInUseException, EntityNotInDatabaseException {
        Item item = new Item(12,"apple",50);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(item);

        inMemoryDatabase.delete(item);
        Exception exception = assertThrows(EntityNotInDatabaseException.class, () -> {
            inMemoryDatabase.delete(item);
        });
        String expectedMessage = "This Object does not exist";
        String exceptionMessage = exception.getMessage();
        assertEquals(expectedMessage,exceptionMessage);
    }
    @Test
    public void findOneTest() throws PrimaryKeyAlreadyInUseException {
        Item item = new Item(12,"apple",50);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(item);

        Item item2 = new Item(50,"RedBull",250);
        inMemoryDatabase.save(item2);

        assertEquals(inMemoryDatabase.findeOne(12l).get(),item);
        assertEquals(inMemoryDatabase.findeOne(50l).get(),item2);
        assertTrue(inMemoryDatabase.findeOne("ah").isEmpty());

    }
    @Test
    public void findAllTest() throws PrimaryKeyAlreadyInUseException {
        Item item = new Item(12,"apple",50);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(item);

        Item item2 = new Item(50,"RedBull",250);
        inMemoryDatabase.save(item2);

        assertTrue(inMemoryDatabase.getDatabase().get(0).equals(item));
        inMemoryDatabase.findAll(Ordering.usingToString());   //alphabetical sorting
        assertTrue(inMemoryDatabase.getDatabase().get(0).equals(item2));
    }

}
