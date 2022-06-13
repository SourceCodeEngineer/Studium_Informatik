package e01;

import java.util.*;

public class InMemoryDatabase<T,U> {

    private ArrayList<Entity> database = new ArrayList();

    public Entity save(Entity entity) throws PrimaryKeyAlreadyInUseException {
        for (Entity x : database) {
            if(x.getKey().equals(entity.getKey())){
                throw new PrimaryKeyAlreadyInUseException("This primary key is already in use: " + x.getKey());
            }
        }
        database.add(entity);
        return entity;
    }

    public Entity delete(Entity entity) throws EntityNotInDatabaseException {
        if(!database.contains(entity)){
            throw new EntityNotInDatabaseException("This Object does not exist");
        }
        database.remove(entity);
        return entity;
    }

    public Optional<Entity> findeOne(U id){
        for (Entity x : database) {
            if(x.getKey().equals(id)){
                return Optional.of(x);
            }
            }
        return Optional.empty();
    }

    List<Entity> findAll(Comparator<Entity> comparator){
        Collections.sort(database,comparator);
        return database;
    }
    public int getSize(){
        return database.size();
    }

    public ArrayList<Entity> getDatabase() {
        return database;
    }

    @Override
    public String toString() {
        return "InMemoryDatabase{" +
                "database=" + database +
                '}';
    }
}
