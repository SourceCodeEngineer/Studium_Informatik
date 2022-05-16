package week08;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public final class Sets {
    public static void main(String[] args) {
        final Set<Integer> emptySet = new HashSet<>();
        final Set<Integer> set1 = new HashSet<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
        final Set<Integer> set2 = new HashSet<>(Arrays.asList(0, 1, 2));
        final Set<Integer> set3 = new HashSet<>(Arrays.asList(2, 3, 4));
        final Set<Integer> set4 = new HashSet<>(Arrays.asList(10, 11, 12));

        System.out.println("Intersections");
        System.out.println(intersection(emptySet, set1));
        System.out.println(intersection(set1, set2));
        System.out.println(intersection(set2, set3));
        System.out.println(intersection(set1, set4));

        System.out.println("Unions");
        System.out.println(union(emptySet, set1));
        System.out.println(union(set1, set2));
        System.out.println(union(set2, set3));
        System.out.println(union(set1, set4));

        System.out.println("Differences");
        System.out.println(difference(emptySet, set1));
        System.out.println(difference(set1, emptySet));
        System.out.println(difference(set1, set2));
        System.out.println(difference(set2, set1));
        System.out.println(difference(set2, set3));
        System.out.println(difference(set3, set2));
        System.out.println(difference(set1, set4));
        System.out.println(difference(set4, set1));

        System.out.println("Symmetric differences");
        System.out.println(symmetricDifference(emptySet, set1));
        System.out.println(symmetricDifference(set1, set2));
        System.out.println(symmetricDifference(set2, set3));
        System.out.println(symmetricDifference(set3, set1));
        System.out.println(symmetricDifference(set3, set4));
        System.out.println(symmetricDifference(set1, set4));
    }

    // do not change the input sets
    public static Set<Integer> intersection(final Set<Integer> set1, final Set<Integer> set2) {
        final Set<Integer> set = new HashSet<>();
        for (Integer i:set1) {
            for (Integer j:set2) {
                if(i == j){
                    set.add(i);
                }
            }
        }
        return set;
    }


    // do not change the input sets
    public static Set<Integer> union(final Set<Integer> set1, final Set<Integer> set2) {
        final Set<Integer> set = new HashSet<>();

        if (set1.isEmpty()){
            return set2;
        } else if(set2.isEmpty()){
            return set1;
        } else {

        for (Integer i : set1) {
            for (Integer j : set2) {
                if(!i.equals(j)){
                    set.add(i);
                    set.add(j);
                }
            }
        }
        return set;
        }
    }

    // do not change the input sets
    public static Set<Integer> difference(final Set<Integer> set1, final Set<Integer> set2) {
        final Set<Integer> set = new HashSet<>();

        // return empty because the given task doesn't specify what we should do exactly, so I do A without B
        if(set1.isEmpty()){
            return set;
        }

        for (int i = 0; i < (set1.size()+set2.size()); ++i) {
            if((set1.contains(i) && (!set2.contains(i)))){
                set.add(i);
            }
        }
        return set;
    }

    // do not change the input sets
    public static Set<Integer> symmetricDifference(final Set<Integer> set1, final Set<Integer> set2) {
        final Set<Integer> set = new HashSet<>();

        if(set1.isEmpty() && set2.isEmpty()){
            return set;
        } else

        if (set1.isEmpty()){
            return set2;
        } else

        if (set2.isEmpty()){
            return set1;
        }

        for (int i = 0; i < (set1.size()+set2.size());i++) {
            if((set1.contains(i)&&(!set2.contains(i))) || (!set1.contains(i)&&(set2.contains(i)))){
                set.add(i);
            }
        }

        return set;
    }
}

