package week05;

import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstIterator {

    private final Queue<Node> queue;

    public static class Node {
        int value;
        Node left;
        Node right;

        Node(int x) {
            value = x;
        }
    }

    public static void main(String[] args) {
        Node root = new Node(13);
        root.left = new Node(10);
        root.right = new Node(19);
        root.left.left = new Node(3);
        root.left.right = new Node(7);
        root.left.left.left = new Node(1);
        root.left.left.right = new Node(4);
        root.right.left = new Node(15);
        root.right.left.right = new Node(17);
        root.right.right = new Node(22);

        BreadthFirstIterator iter = new BreadthFirstIterator(root);

        System.out.println("hasNext: " + iter.hasNext());
        for (int i = 0; i < 10; i++)
            System.out.println("next: " + iter.next());
        System.out.println("hasNext: " + iter.hasNext());
    }

    public BreadthFirstIterator(Node root) {
        queue = new LinkedList<>();
        queue.add(root);
    }

    /**
     * @return whether we have a next node
     */
    public boolean hasNext() {
        return (!queue.isEmpty());
    }

    /**
     * @return the next node
     */
    public int next() {
        Node temp = queue.poll();
        assert temp != null;

        if (temp.left != null) {
            queue.add(temp.left);
        }
        if (temp.right != null) {
            queue.add(temp.right);
        }
        return temp.value;
    }
}