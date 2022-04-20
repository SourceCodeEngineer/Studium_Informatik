package at.ac.uibk.pm.g05.csaz7620.s04.e03;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Calendar;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

public class PasswordCheckerTest {
    @Deprecated
    User rootUser = new User("Root", "System", new Date(1996, Calendar.JANUARY, 23));
    PasswordChecker passwordChecker = new PasswordChecker();

    @Test
    public void emptyPassword() {
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            passwordChecker.checkPassword(rootUser, "");
        });
        String expectedMessage = "Password can't be empty!";
        String exceptionMessage = exception.getMessage();
        Assertions.assertEquals("Password can't be empty!", exceptionMessage);
    }

    @Test
    public void nullValues() {
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            passwordChecker.checkPassword(rootUser, null);
        });

        String expectedMessage = "Password can't be a null value";
        String exceptionMessage = exception.getMessage();
        Assertions.assertEquals(expectedMessage, exceptionMessage);

        Exception exception2 = assertThrows(IllegalArgumentException.class, () -> {
            User user = new User(null, null, new Date());
        });

        String expectedMessage2 = "Invalid User parameters!";
        String exceptionMessage2 = exception2.getMessage();
        Assertions.assertEquals(expectedMessage2, exceptionMessage2);

        Exception exception3 = assertThrows(IllegalArgumentException.class, () -> {
            User user = new User("", "System", new Date());
        });

        String expectedMessage3 = "Invalid User parameters!";
        String exceptionMessage3 = exception3.getMessage();
        Assertions.assertEquals(expectedMessage3, exceptionMessage3);

    }

    @Test
    public void illegalCharTest() {
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            passwordChecker.checkPassword(rootUser, "§");
        });

        String expectedMessage = "Invalid character!";
        String exceptionMessage = exception.getMessage();
        Assertions.assertEquals(expectedMessage, exceptionMessage);

        Exception exception2 = assertThrows(IllegalArgumentException.class, () -> {
            passwordChecker.checkPassword(rootUser, ";");
        });

        String expectedMessage2 = "Invalid character!";
        String exceptionMessage2 = exception2.getMessage();
        Assertions.assertEquals(expectedMessage2, exceptionMessage2);
    }

    @Test
    public void containsEnoughChars() {

        String passwordNotEnoughChars = "A";
        int strength = passwordChecker.checkRules(rootUser, passwordNotEnoughChars);
        assertEquals(strength, 1);

        String passwordEnoughChars = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; // 42 A's
        int strength2 = passwordChecker.checkRules(rootUser, passwordEnoughChars);
        assertEquals(strength2, 3);

        String passwordNotEnoughChars2 = "AAAAAAAAA";
        int strength3 = passwordChecker.checkRules(rootUser, passwordNotEnoughChars2);
        assertEquals(strength3, 2);
    }

    @Test
    public void containsTwoOrMoreNumbers() {
        String passwordTwoNumbers = "22";
        int strength = passwordChecker.checkRules(rootUser, passwordTwoNumbers);
        assertEquals(strength, 2);

        String passwordOneNumber = "1";
        int strength2 = passwordChecker.checkRules(rootUser, passwordOneNumber);
        assertEquals(strength2, 1); //Rule 6
    }

    @Test
    public void containsThreeOrMoreLowerCase() {
        String passwordThreeLowerCase = "aaa";
        int strength = passwordChecker.checkRules(rootUser, passwordThreeLowerCase);
        assertEquals(strength, 2);

        String passwordOneChar = "A";
        int strength2 = passwordChecker.checkRules(rootUser, passwordOneChar);
        assertEquals(strength2, 1);

    }

    @Test
    public void containsTwoOrMoreUpperCase() {
        String passwordTWOUpperCase = "AA";
        int strength = passwordChecker.checkRules(rootUser, passwordTWOUpperCase);
        assertEquals(strength, 2);

        String passwordOneChar = "A";
        int strength2 = passwordChecker.checkRules(rootUser, passwordOneChar);
        assertEquals(strength2, 1);

    }

    @Test
    public void containsTwoSpecialChars() {
        String passwordSpecial = "?!";
        int strength = passwordChecker.checkRules(rootUser, passwordSpecial);
        assertEquals(strength, 2);
    }

    @Test
    public void containsUserInformation() {
        String passwordName = "Root";
        int strength = passwordChecker.checkRules(rootUser, passwordName);
        assertEquals(strength, 1);

        String passwordLastName = "System";
        int strength2 = passwordChecker.checkRules(rootUser, passwordLastName);
        assertEquals(strength2, 1);

        String passwordDate = "19960123";
        int strength3 = passwordChecker.checkRules(rootUser, passwordDate);
        assertEquals(strength2, 1);

    }

    @Test
    public void tooWeakPasswordTest() {
        String password = "ab";
        PasswordStrength passwordStrength = passwordChecker.checkPassword(rootUser, password);
        assertEquals(passwordStrength, PasswordStrength.TOO_WEAK);
        assertNotEquals(passwordStrength, PasswordStrength.WEAK);
        assertNotEquals(passwordStrength, PasswordStrength.MEDIUM);
        assertNotEquals(passwordStrength, PasswordStrength.STRONG);
    }

    @Test
    public void weakPasswordTest() {
        String password = "ab13";
        PasswordStrength passwordStrength = passwordChecker.checkPassword(rootUser, password);
        assertNotEquals(passwordStrength, PasswordStrength.TOO_WEAK);
        assertEquals(passwordStrength, PasswordStrength.WEAK);
        assertNotEquals(passwordStrength, PasswordStrength.MEDIUM);
        assertNotEquals(passwordStrength, PasswordStrength.STRONG);
    }

    @Test
    public void MediumPasswordTest() {
        String password = "ab13AB"; //Rule 2,6 and 4
        PasswordStrength passwordStrength = passwordChecker.checkPassword(rootUser, password);
        assertNotEquals(passwordStrength, PasswordStrength.TOO_WEAK);
        assertNotEquals(passwordStrength, PasswordStrength.WEAK);
        assertEquals(passwordStrength, PasswordStrength.MEDIUM);
        assertNotEquals(passwordStrength, PasswordStrength.STRONG);
    }

    @Test
    public void strongPasswordTest() {
        String password = "1337LEETsp33ch!sNICE";
        PasswordStrength passwordStrength = passwordChecker.checkPassword(rootUser, password);
        assertNotEquals(passwordStrength, PasswordStrength.TOO_WEAK);
        assertNotEquals(passwordStrength, PasswordStrength.WEAK);
        assertNotEquals(passwordStrength, PasswordStrength.MEDIUM);
        assertEquals(passwordStrength, PasswordStrength.STRONG);
    }
}