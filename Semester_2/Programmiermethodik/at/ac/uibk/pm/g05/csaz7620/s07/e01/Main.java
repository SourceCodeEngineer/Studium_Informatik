package e01;

public class Main {
    public static void main(String[] args) throws PrimaryKeyAlreadyInUseException {
        System.out.println("Ausgabe aus der main()-Methode");
        Entity entity = new Entity<>(123,"abc");
        Entity entity2 = new Entity<>("wdwq",5);
        InMemoryDatabase inMemoryDatabase = new InMemoryDatabase();
        inMemoryDatabase.save(entity);
        inMemoryDatabase.save(entity2);
        System.out.println(inMemoryDatabase);

    }
}
