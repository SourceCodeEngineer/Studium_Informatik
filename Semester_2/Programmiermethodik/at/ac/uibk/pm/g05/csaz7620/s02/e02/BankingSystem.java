package at.ac.uibk.pm.g05.csaz7620.s02.e02;

import java.util.List;

public class BankingSystem {
    private List<BankAccount> managedBankAccounts;

    public List<BankAccount> getManagedBankAccounts() {
        return managedBankAccounts;
    }

    public void setManagedBankAccounts(List<BankAccount> managedBankAccounts) {
        this.managedBankAccounts = managedBankAccounts;
    }

    public void addBankAccountToManagedOnes(BankAccount bankaccount){
        this.managedBankAccounts.add(bankaccount);
    }
}
