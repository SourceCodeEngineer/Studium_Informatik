package e02;

import java.io.BufferedReader;
import java.io.IOException;
import java.math.BigDecimal;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

public class CSVToArray {

    private static final String CSV_DELIMITER = ",";

    private CSVToArray() {

    }

    public static List<Item> readCsv(Path filename) throws IOException {
        List<Item> items = new ArrayList<>();
        try (BufferedReader br = Files.newBufferedReader(filename)) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(CSV_DELIMITER);
                Item item = extractItem(values);
                items.add(item);
            }
        }
        return items;
    }

    private static Item extractItem(String[] attributes) {
        String name = attributes[0];
        int foodType = Integer.parseInt(attributes[1]);
        BigDecimal price = new BigDecimal(attributes[2]);
        DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("d/M/yyyy");
        LocalDate date = LocalDate.parse(attributes[3], dateFormatter);
        return new Item(name, FoodType.values()[foodType], price, date);
    }

}

