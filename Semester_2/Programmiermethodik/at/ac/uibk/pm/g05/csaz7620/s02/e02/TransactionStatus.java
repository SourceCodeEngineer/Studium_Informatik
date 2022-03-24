package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class TransactionStatus {
    private String transactionStatus;

    public TransactionStatus(String transactionStatus) {
        setTransactionStatus(transactionStatus);
    }

    public String getTransactionStatus() {
        return transactionStatus;
    }

    public void setTransactionStatus(String transactionStatus) {
        this.transactionStatus = transactionStatus;
    }
}
