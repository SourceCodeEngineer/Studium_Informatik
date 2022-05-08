package at.ac.uibk.pm.g05.csaz7620.s05.e03;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class Main {

    public static void main(String[] args) {

        /**
         * The data was generated by a random selection from lists and a match with real
         * persons is purely coincidental.
         */
        String[] csv = {
                "Li Kim,Kranewitterstraße 4;6020;Innsbruck;Austria,09.12.1997,passe-temps:aNT-KEepINg",
                "Nour Vargas,Serlesweg 2;6020;Innsbruck;Austria,22.01.1995,aficiones:SURvIVAlISm;kung Fu;ROBOt cOmbat",
                "Aleksandr Houssein,Seilergasse 6;6020;Innsbruck;Austria,08.04.1999,aficiones:GYmNASTIcs",
                "Jelena Pierre,Josef-Wilberger-Straße 1;6020;Innsbruck;Austria,20.11.1996,passe-temps:rEsEaRch;BUSinESS",
                "Monika Madrid,Lehmweg 3;6020;Innsbruck;Austria,05.01.1993,passe-temps:pRoVErBs;mAgiC;fOsSICkIng",
                "Fatouma Khan,Lutterottistraße 7;6020;Innsbruck;Austria,28.12.1995,passe-temps:meTALwoRKING;reCoRd CoLlecting",
                "Mohamed Rodriguez,Cranachstraße 6;6020;Innsbruck;Austria,03.06.1993,aficiones:MaCrAmE",
                "Md Memmedov,Prinz-Eugen Brücke 10;6020;Innsbruck;Austria,04.07.1991,aficiones:KNoWleDge/wOrd gameS;ENTertaInInG",
                "Dimitris Martin,Gsturnsteig 10;6020;Innsbruck;Austria,21.02.1990,passe-temps:elEctRONIc GAMes;vintAge cArs;HorsEShoeS",
                "Mpho Rusu,Heiligwasserwiese 1;6020;Innsbruck;Austria,02.08.1990,aficiones:CLimbinG;wEIghT trAINInG",
        };

        List<Person> persons = new ArrayList<>();

        for (int i = 0; i < csv.length; i++) {
            String csv_row = csv[i];
            String [] splitted = csv_row.split(",");
            String name = splitted[0];
            String address = splitted[1];
            String birthday = splitted[2];
            String hobbies = splitted[3];

            String [] addressSplitted = address.split(";");
            String street = addressSplitted[0];
            String housenumber = "";
            
            for(int j = 0; j < street.length();j++){
                if(Character.isDigit(street.charAt(j))){
                    housenumber = street.substring(j, street.length()) + housenumber;
                    street = street.substring(0,j-1);
                }
            }
            char[] housenumberArray = housenumber.toCharArray();
            char firstNumber = housenumberArray[0];
            if(firstNumber == '0'){
                housenumber = housenumber.substring(1,housenumber.length());
            }

            String zipCodeString = addressSplitted[1];
            int zipCode = Integer.parseInt(zipCodeString);
            String city = addressSplitted[2];
            String country = addressSplitted[3];

            Address address1 = new Address(street,housenumber,zipCode,city,country);

            String [] nameSplitted = name.split(" ");
            String firstName = nameSplitted[0];
            String lastName = nameSplitted[1];
            System.out.println(lastName);

            String[] hobbiesSplitted = hobbies.split(":");
            String hobbiesSplitted2 = hobbiesSplitted[1];
            String[] formatedHobbies = hobbiesSplitted2.split(";");

            for(int j = 0; j<formatedHobbies.length;j++){
                formatedHobbies[j] = formatedHobbies[j].toLowerCase();
            }
            Person person = new Person(firstName,lastName,address1,birthday,formatedHobbies);
            persons.add(person);

        }

        for (int i = 0; i < persons.size(); i++) {
            System.out.println(persons.get(i));
            System.out.println("***********************************************************");
        }

    }
}
