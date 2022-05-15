package at.ac.uibk.pm.g05.csaz7620.s06.e01;

import java.util.Iterator;

public class FibonacciIterator implements Iterator<Integer> {

    private int n;
    int index = 0;
    int prevVal = 0;
    int curVal = 1;

    public FibonacciIterator(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("You need a value bigger then 0!");
        }
        this.n = n;
    }

    @Override
    public boolean hasNext() {
        return (index < n);
    }

    @Override
    public Integer next() {
        if(hasNext() == false){
            throw new IndexOutOfBoundsException("This fibonacci Iterator can only create values to the index " + this.n);
        }
        int answer = this.prevVal + this.curVal;
        this.prevVal = this.curVal;
        this.curVal = answer;
        ++index;
        return answer;
    }
}
