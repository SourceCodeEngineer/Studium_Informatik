package at.ac.uibk.pm.g05.csaz7620.s07.e01;

public class EntityNotInDatabaseException extends Exception {
    public EntityNotInDatabaseException(String this_object_does_not_exist) {
        super(this_object_does_not_exist);
    }
}
