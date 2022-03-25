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
}
