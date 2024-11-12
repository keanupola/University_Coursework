package edu.utsa.cs3443.tro893_lab3.model;

/**
 * Represents a commercial property with additional attributes: zone, number of units, and
 * number of parking spots.
 *
 * @author Keanu Anderson-Pola
 * @abc123 tro893
 */
public class CommercialProperty extends Property {
    private String zone;
    private int numUnits;
    private int numParkingSpots;

    // Constructor
    public CommercialProperty(String id, String location, double price, String zone, int numUnits, int numParkingSpots) {
        super(id, location, price);
        this.zone = zone;
        this.numUnits = numUnits;
        this.numParkingSpots = numParkingSpots;
    }

    // Getters and setters
    /**
     * Gets the zone for this commercial property.
     * @return string, the property's zone
     */
    public String getZone() { return zone; }
    /**
     * Sets the zone for this commercial property.
     * @param zone, the property's zone (string)
     */
    public void setZone(String zone) { this.zone = zone; }

    /**
     * Gets the number of units for this commercial property
     * @return int, the number of units at this property
     */
    public int getNumUnits() { return numUnits; }
    /**
     * Sets the number of units this commercial property
     * @param numUnits, the number of units at this property (int)
     */
    public void setNumUnits(int numUnits) { this.numUnits = numUnits; }

    /**
     * Gets the number of parking spots for this commercial property
     * @return int, the number of parking spots at this property
     */
    public int getNumParkingSpots() { return numParkingSpots; }
    /**
     * Sets the number of parking spots for this commercial property
     * @param numParkingSpots, the number of parking spots at this property
     */
    public void setNumParkingSpots(int numParkingSpots) { this.numParkingSpots = numParkingSpots; }

    /**
     * Returns a string representation of the CommercialProperty object,
     * including the zone, number of units, and the number of parking spots
     *
     * @return string representation of the CommercialProperty
     */
    @Override
    public String toString() {
        return super.toString() + ", Zone: " + zone + ", Number of Units: " + numUnits + ", Number of Parking Spots: " + numParkingSpots;
    }

}