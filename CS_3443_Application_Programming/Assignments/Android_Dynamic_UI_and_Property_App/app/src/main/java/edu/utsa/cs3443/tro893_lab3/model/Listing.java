package edu.utsa.cs3443.tro893_lab3.model;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.InputStream;
import android.content.res.AssetManager;

import edu.utsa.cs3443.tro893_lab3.MainActivity;

/**
 * This class creates and manages a list of properties, allowing for property loading and retrieval
 *
 * @author Keanu Anderson-Pola
 * @abc123 tro893
 */
public class Listing {
    private ArrayList<Property> properties;

    // Constructor
    public Listing() {
        // initialized to empty list
        this.properties = new ArrayList<>();
    }


    /**
     * Loads properties from "listings.csv" in assets
     *
     * @param activity, the main activity used to access the assets
     */
    public void loadProperties(MainActivity activity) {
        // Get the AssetManager from the provided activity to access the app's assets
        AssetManager manager = activity.getAssets();

        // Initialize the properties list if it's null
        if (properties == null) {
            properties = new ArrayList<>();
        }

        String filename = "listings.csv";
        try {
            // Open the CSV file for reading
            InputStream file = manager.open(filename);
            Scanner scan = new Scanner(file);

            String line; // Temp line var

            // Loop through each line in the CSV file
            while (scan.hasNextLine()) {
                line = scan.nextLine();
                String[] tokens = line.split(","); // split lines at ","

                String id = tokens[0].trim();
                String location = tokens[1].trim();
                double price = Double.parseDouble(tokens[2].trim());

                // Check property type and create the appropriate object
                if (id.startsWith("rp")) {
                    double annualHOAFees = Double.parseDouble(tokens[3].trim());
                    int numBedrooms = Integer.parseInt(tokens[4].trim());
                    double numBathrooms = Double.parseDouble(tokens[5].trim());
                    properties.add(new ResidentialProperty(id, location, price, annualHOAFees, numBedrooms, numBathrooms));
                } else if (id.startsWith("cp")) {
                    String zone = tokens[3].trim();
                    int numUnits = Integer.parseInt(tokens[4].trim());
                    int numParkingSpots = Integer.parseInt(tokens[5].trim());
                    properties.add(new CommercialProperty(id, location, price, zone, numUnits, numParkingSpots));
                }
            }
            // Close scanner
            scan.close();
        } catch (IOException e) {
            System.out.println("Failed to read data");
        }
    }

    /**
     * Returns a property based on its address
     *
     * @param address, the property's address
     * @return Property, the property with the address, or null if DNE
     */
    public Property getProperty(String address) {
        for (Property property : properties) {
            if (property.getLocation().equals(address)) {
                return property;
            }
        }
        return null;
    }

    /**
     * Returns a list of all properties in the listing.
     * @return ArrayList of all properties
     */
    public ArrayList<Property> getProperties() {
        return properties;
    }


}
