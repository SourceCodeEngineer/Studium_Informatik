package at.ac.uibk.pm.g05.csaz7620.s05.e01;

import java.util.Objects;

public class MyCustomClass2 extends Object {

    private Integer attribute1;
    private String attribute2;
    private Double attribute3;
    private int attribute4;

    public MyCustomClass2(Integer attribute1, String attrubute2, Double attrubute3, int attribute4) {
        this.attribute1 = attribute1;
        this.attribute2 = attrubute2;
        this.attribute3 = attrubute3;
        this.attribute4 = attribute4;
    }

    @Override
    public String toString() {
        return "MyCustomClass2{" +
                "attribute1=" + attribute1 +
                ", attribute2='" + attribute2 + '\'' +
                ", attribute3=" + attribute3 +
                ", attribute4=" + attribute4 +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        MyCustomClass2 that = (MyCustomClass2) o;
        return attribute4 == that.attribute4 && Objects.equals(attribute1, that.attribute1) && Objects.equals(attribute2, that.attribute2) && Objects.equals(attribute3, that.attribute3);
    }
}
