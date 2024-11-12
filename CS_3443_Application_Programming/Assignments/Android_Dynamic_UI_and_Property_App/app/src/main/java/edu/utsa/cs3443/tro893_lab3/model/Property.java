package edu.utsa.cs3443.tro893_lab3.model;

/**
 * Represents a generic property with attributes: id, location, and price.
 *
 * @author Keanu Anderson-Pola
 * @abc123 tro893
 */
public abstract class Property {
    private String id;
    private String location;
    private double price;

    // Constructor
    public Property(String id, String location, double price) {
        this.id = id;
        this.location = location;
        this.price = price;
    }

    // Getters and setters
    /**
     * Returns the ID of the property.
     * @return property ID
     */
    public String getId() { return id; }
    /**
     * Sets the ID of the property.
     * @param id, property id (string)
     */
    public void setId(String id) { this.id = id; }

    /**
     * Returns the location of the property.
     * @return string, property location
     */
    public String getLocation() { return location; }
    /**
     * Sets the location of the property.
     * @param location, property location (string)
     */
    public void setLocation(String location) { this.location = location; }

    /**
     * Returns the price of the property.
     * @return double, property price
     */
    public double getPrice() { return price; }
    /**
     * Sets the price of the property.
     * @param price, property price (double)
     */
    public void setPrice(double price) { this.price = price; }

    /**
     * Returns a string representation of the Property object,
     * the property id, address (location), and the property amount (price).
     *
     * @return string representation of the Property.
     */
    @Override
    public String toString() {
        return "Property ID: " + id + ", Location: " + location + ", Price: $" + price;
    }

}

