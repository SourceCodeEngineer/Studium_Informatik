package at.ac.uibk.pm.g05.csaz7620.s08.e03;

public class EagerChecker {

    static String eagerChecker(boolean first, boolean second) {
        return first && second ? "match" : "incompatible!";
    }

}
