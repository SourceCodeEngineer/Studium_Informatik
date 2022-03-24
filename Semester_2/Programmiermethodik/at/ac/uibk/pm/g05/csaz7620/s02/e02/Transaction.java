package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class Transaction {
    public boolean transaction(BankAccount customerSource, BankAccount customerTarget, int transferAmount){
        if(BankAccount.withdrawAllowed(transferAmount, customerSource, customerSource.getCustomer().getCreditrating())){
            customerSource.withdraw(transferAmount, customerSource);
            customerTarget.deposit(transferAmount, customerTarget);
            return true;
        }
        return false;
    }
}
