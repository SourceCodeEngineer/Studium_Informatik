package e01;

public class EntityNotInDatabaseException extends Exception {
    public EntityNotInDatabaseException(String this_object_does_not_exist) {
        super(this_object_does_not_exist);
    }
}
