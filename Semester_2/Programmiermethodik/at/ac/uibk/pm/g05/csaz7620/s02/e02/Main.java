package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class Main {
    public static void main(String[] args) {
        // creating BankAccount 1:
        BankingSystem bankingSystem = new BankingSystem();
        Customer customer1 = new Customer("John", "Doe", CreditRating.low);
        BankAccount bankAccountTest1 = new BankAccount("at54 1200 0100 2222 2222", customer1, 500);

        Customer customer2 = new Customer("Jane", "Doe", CreditRating.high);
        BankAccount bankAccountTest2 = new BankAccount("at54 1200 0100 1111 1111", customer2, 700);

        bankAccountTest1.deposit(200, bankAccountTest1);
        bankAccountTest2.withdraw(200, bankAccountTest2);

        bankAccountTest2.deposit(100, bankAccountTest2);
        bankAccountTest1.withdraw(100, bankAccountTest1);


        bankingSystem.transferFromTo(bankAccountTest1, bankAccountTest2, 100);

        bankingSystem.printTransfers();
    }
}
