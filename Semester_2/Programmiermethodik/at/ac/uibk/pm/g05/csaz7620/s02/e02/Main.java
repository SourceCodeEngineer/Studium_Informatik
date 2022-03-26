package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class Main {
    public static void main(String[] args) {
        // creating BankAccount 1:
        Customer customer1 = new Customer("John", "Doe", CreditRating.low);
        BankAccount bankAccountTest1 = new BankAccount("at54 1200 0100 2222 2222", customer1, 200);

        Customer customer2 = new Customer("Jane", "Doe", CreditRating.high);
        BankAccount bankAccountTest2 = new BankAccount("at54 1200 0100 1111 1111", customer2, 700);

        bankAccountTest1.deposit(200, bankAccountTest1);
        bankAccountTest2.withdraw(200, bankAccountTest2);

        BankingSystem.transferFromTo(bankAccountTest1, bankAccountTest2, 100);
        System.out.println("finish");
    }
}
