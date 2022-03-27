package at.ac.uibk.pm.g05.csaz7620.s02.e02;

import java.util.ArrayList;

public class BankingSystem {
    private ArrayList<BankAccount> managedBankAccountsArrayList = new ArrayList<>();
    private ArrayList<Transaction> transactionsArrayList = new ArrayList<>();

    public ArrayList<BankAccount> getManagedBankAccounts() {
        return managedBankAccountsArrayList;
    }

    public void setManagedBankAccounts(ArrayList<BankAccount> managedBankAccounts) {
        this.managedBankAccountsArrayList = managedBankAccounts;
    }

    public void addBankAccountToManagedOnes(BankAccount bankaccount){
        this.managedBankAccountsArrayList.add(bankaccount);
    }

    public void createBankAccount(String iban, Customer customer, long balance){
        BankAccount bankaccount = new BankAccount(iban, customer, balance);
        addBankAccountToManagedOnes(bankaccount);
    }

    public void transferFromTo(BankAccount bankAccountSource, BankAccount bankAccountDest, long amount){
        TransactionStatus status;
        if(BankAccount.withdrawAllowed(amount, bankAccountSource, bankAccountSource.getCustomer().getCreditRating())){
            status = TransactionStatus.success;
        }
        else {
            status = TransactionStatus.failure;
        }
        Transaction transaction = new Transaction(status, bankAccountSource, bankAccountDest, amount);
        transactionsArrayList.add(transaction);

        if(status == TransactionStatus.success){
            bankAccountSource.withdraw(amount, bankAccountSource);
            bankAccountDest.deposit(amount, bankAccountDest);
        }
    }

    public ArrayList<Transaction> getTransactionsArrayList() {
        return transactionsArrayList;
    }

    public void printTransfers() {
        for (int i = 0; i < transactionsArrayList.size(); ++i){
            System.out.println(transactionsArrayList.get(i).getSource().getIban());
            System.out.println(transactionsArrayList.get(i).getDest().getIban());
            System.out.println(transactionsArrayList.get(i).getAmount());
            System.out.println(transactionsArrayList.get(i).getStatus());
        }
    }
}
