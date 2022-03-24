package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class BankAccount {
    private String iban;
    private Customer customer;
    private long balance;

    public BankAccount(String iban, Customer customer, long balance) {
        setIban(iban);
        setCustomer(customer);
        setBalance(balance);
    }

    public void deposit(int money, BankAccount bankaccount){
        //todo implement function deposit
    }

    public void withdraw(int money, BankAccount bankaccount){
        //todo implement function withdraw
    }

    public String getIban() {
        return iban;
    }

    public void setIban(String iban) {
        this.iban = iban;
    }

    public Customer getCustomer() {
        return customer;
    }

    public void setCustomer(Customer customer) {
        this.customer = customer;
    }

    public long getBalance() {
        return balance;
    }

    public void setBalance(long balance) {
        this.balance = balance;
    }
}
