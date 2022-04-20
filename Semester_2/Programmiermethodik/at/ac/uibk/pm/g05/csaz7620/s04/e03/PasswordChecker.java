package at.ac.uibk.pm.g05.csaz7620.s04.e03;

public class PasswordChecker {

    private char[] charArray = {'?', '!', '%', '&', '=', '[', ']', '+', '-'};

    public PasswordStrength checkPassword(User user, String password) throws IllegalArgumentException{

        try {
            if (password.isEmpty()) {
                throw new IllegalArgumentException("Password can't be empty!");
            } else {
                int passwordStrength = checkRules(user, password);

                if (passwordStrength < 2) {
                    return PasswordStrength.TOO_WEAK;
                }
                else if (passwordStrength == 2) {
                    return PasswordStrength.WEAK;
                }
                else if (passwordStrength > 2 && passwordStrength < 5) {
                    return PasswordStrength.MEDIUM;
                } else {
                    return PasswordStrength.STRONG;
                }
            }
        }

        catch (NullPointerException x){
            throw new IllegalArgumentException("Password can't be a null value");
        }
    }

    public int checkRules(User user, String password) throws IllegalArgumentException {
        int strength = 0;

        if(password.length() > 15){
            ++strength;
        }

        int numbers = 0;
        int lowerCase = 0;
        int upperCase = 0;
        int specialChars = 0;

        char[] charPassword = password.toCharArray(); // creates an array of char, so we can iterate over it.

        // we check for every char of the char array if it is a number, upper lower or special character.
        for(char character : charPassword) {
            if (Character.isDigit(character)) {
                ++numbers;
            } else {
                if (Character.isLowerCase(character)) {
                    ++lowerCase;
                } else {
                    if (Character.isUpperCase(character)) {
                        ++upperCase;
                    } else {
                        if (!(new String(charArray).contains(new String(String.valueOf(character))))) {
                            ++specialChars;
                        }
                        else {
                            throw new IllegalArgumentException("Invalid character!");
                        }
                    }
                }
            }
        }

        if(password.contains(user.getFirstName()) == false && password.contains(user.getLastName())== false && password.contains(user.getBirthDate().toString()) == false){
            ++strength;
        }

        if(numbers > 1){
            ++strength;
        }
        if(lowerCase > 2){
            ++strength;
        }
        if(upperCase > 1){
            ++strength;
        }
        if(specialChars > 1){
            ++strength;
        }
        return strength;
    }
}
