package at.ac.uibk.pm.g05.csaz7620.s05.e03;

public class Address {

    private String street;
    private String houseNumber;
    private int zipCode;
    private String city;
    private String country;

    public Address(String street, String housenum, int zipCode, String city, String country) {
        this.street = street;
        this.houseNumber = housenum;
        this.zipCode = zipCode;
        this.city = city;
        this.country = country;
    }

    @Override
    public String toString() {
        return "Address{" +
                "street='" + street + '\'' +
                ", houseNumber='" + houseNumber + '\'' +
                ", zipCode=" + zipCode +
                ", city='" + city + '\'' +
                ", country='" + country + '\'' +
                '}';
    }
}
