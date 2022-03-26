package at.ac.uibk.pm.g05.csaz7620.s02.e02;

public class Transaction {
    private TransactionStatus status;
    private BankAccount source;
    private BankAccount dest;
    private long amount;

    public Transaction(TransactionStatus status, BankAccount source, BankAccount dest, long amount) {
        setStatus(status);
        setSource(source);
        setDest(dest);
        setAmount(amount);
    }

    public TransactionStatus getStatus() {
        return status;
    }

    public void setStatus(TransactionStatus status) {
        this.status = status;
    }

    public BankAccount getSource() {
        return source;
    }

    public void setSource(BankAccount source) {
        this.source = source;
    }

    public BankAccount getDest() {
        return dest;
    }

    public void setDest(BankAccount dest) {
        this.dest = dest;
    }

    public long getAmount() {
        return amount;
    }

    public void setAmount(long amount) {
        this.amount = amount;
    }
}
