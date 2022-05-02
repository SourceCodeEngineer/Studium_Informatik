package at.pm.cxxxxxxx.ex3;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/*
All operations have a worst case time complexity of O(n).
 */
public class SortedList<T extends Comparable<? super T>> {
    private final List<T> internalList = new ArrayList<>();

    public void addElement(T element) {
        /*
        Binary search has time complexity O(log(n))
        Insertion has time complexity O(n)

        Time complexity: O(n)
         */
        int index = Collections.binarySearch(internalList, element);
        int insertionPoint = index >= 0 ? index : -index - 1;
        internalList.add(insertionPoint, element);
    }

    public void removeElement(T element) {
        /*
        Deletion has time complexity O(n)

        Time complexity: O(n)
         */
        internalList.remove(element);
    }

    public List<T> getSorted() {
        /*
        Copying has time complexity O(n)

        Time complexity: O(n)
         */
        return new ArrayList<>(internalList);

        /*
        Alternative: Return a unmodifiable list.

        Time complexity: O(1)
        return Collections.unmodifiableList(internalList);
        */
    }
}