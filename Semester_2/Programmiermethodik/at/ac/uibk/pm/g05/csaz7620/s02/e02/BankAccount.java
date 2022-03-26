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

    public void deposit(long money, BankAccount bankaccount){
        bankaccount.setBalance(bankaccount.getBalance() + money);
    }

    public void withdraw(long money, BankAccount bankaccount){
        if(withdrawAllowed(money, bankaccount, bankaccount.customer.getCreditRating())){
            bankaccount.setBalance(bankaccount.getBalance() - money);
        }
        else{
            System.err.println("Not allowed!");
        }
    }


    public static boolean withdrawAllowed(long money, BankAccount bankaccount, CreditRating creditrating){
        if(creditrating == CreditRating.low){
            return (bankaccount.getBalance()-money)>(-100);
        }
        if(creditrating == CreditRating.medium){
            return (bankaccount.getBalance()-money)>(-500);
        }
        return (bankaccount.getBalance()-money)>(-1000);
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
