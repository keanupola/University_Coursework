package edu.utsa.cs3443.tro893_lab3.model;

/**
 * Represents a residential property with additional attributes: annual HOA fees,
 * number of bedrooms, and number of bathrooms.
 *
 * @author Keanu Anderson-Pola
 * @abc123 tro893
 */
public class ResidentialProperty extends Property {
    private double annualHOAFees;
    private int numBedrooms;
    private double numBathrooms;

    // Constructor
    public ResidentialProperty(String id, String location, double price, double annualHOAFees, int numBedrooms, double numBathrooms) {
        super(id, location, price);
        this.annualHOAFees = annualHOAFees;
        this.numBedrooms = numBedrooms;
        this.numBathrooms = numBathrooms;
    }

    // Getters and setters
    /**
     * Gets annual HOA fees for this residential property.
     * @return double, annual HOA fees
     */
    public double getAnnualHOAFees() { return annualHOAFees; }
    /**
     * Sets annual HOA fees for this residential property.
     * @param annualHOAFees (double)
     */
    public void setAnnualHOAFees(double annualHOAFees) { this.annualHOAFees = annualHOAFees; }

    /**
     * Gets number of bedrooms for this residential property.
     * @return int, number of bedrooms
     */
    public int getNumBedrooms() { return numBedrooms; }
    /**
     * Sets number of bedrooms for this residential property.
     * @param numBedrooms, number of bedrooms (int)
     */
    public void setNumBedrooms(int numBedrooms) { this.numBedrooms = numBedrooms; }

    /**
     * Gets number of bathrooms for this residential property.
     * @return int, number of bathrooms
     */
    public double getNumBathrooms() { return numBathrooms; }
    /**
     * Sets number of bathrooms for this residential property.
     * @param numBathrooms, number of bathrooms (int)
     */
    public void setNumBathrooms(double numBathrooms) { this.numBathrooms = numBathrooms; }

    /**
     * Returns a string representation of the ResidentialProperty object,
     * including the annual HOA fees, number of bedrooms, and number of bathrooms.
     *
     * @return string representation of the ResidentialProperty.
     */
    @Override
    public String toString() {
        return super.toString() + ", Annual HOA Fees: $" + annualHOAFees + ", Number of Bedrooms: " + numBedrooms + ", Number of Bathrooms: " + numBathrooms;
    }

}