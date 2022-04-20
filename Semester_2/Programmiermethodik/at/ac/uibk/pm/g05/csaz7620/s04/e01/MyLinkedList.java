package at.ac.uibk.pm.g05.csaz7620.s04.e01;

public class MyLinkedList {
    private Node head;
    private Node tail;
    private int size;

    public void add(String element) {
        if (element == null){
            throw new IllegalArgumentException("Argument must not be null!");
        }
        Node node = new Node(element);
        if (tail == null) {
            tail = node;
            head = node;
        } else {
            tail.setNext(node);
            tail = node;
        }
        ++size;
    }

    public String get(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of Bounds");
        }
        Node current = head;
        for (int i = 0; i < index; ++i) {
            current = current.getNext();
        }
        return current.getElement();
    }

    public int getSize() {
        return size;
    }

}
