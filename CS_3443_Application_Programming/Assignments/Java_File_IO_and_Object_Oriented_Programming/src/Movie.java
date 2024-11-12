/**
 * Movie is a class that represents a movie with a specific name and rating, and contains a list of characters featured in the movie.
 * @see MovieCharacter
 * The class provides functionality to load these characters from a specified CSV file.
 *
 * @author Keanu Anderson-Pola
 */

import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Movie {

    private String name;   // Movie name
    private String rating; // PG13
    private ArrayList<MovieCharacter> characters; // Arraylist of MovieChracter objects

    // Constructors
    public Movie(String name, String rating) {
        this.name = name;
        this.rating = rating;
        this.characters = new ArrayList<>();
    }
    // Without rating
    public Movie(String name) {
    	// Using NR (No Rating) as a placeholder for rating
    	this(name, "NR");
        this.characters = new ArrayList<>();
    }
    
    /**
     * Takes in a file name and adds a MovieCharacter to the Movie for each character in the file.
     *
     */
    public void loadCharacters(String filename) throws FileNotFoundException {
        File file = new File("data/" + filename); // Create File obj. using data directory
        Scanner scanner = new Scanner(file); // Open scanner object
        while(scanner.hasNextLine()) {
        	// Initialize line variable and replace it with each subsequent line throughout
            String line = scanner.nextLine();
            // Separate string at "," and store those into "values" 
            String[] values = line.split(",");
            // CSV format: actorName, characterName, gender, duty
            // Store "values" into movieCharacter object
            MovieCharacter movieCharacter = new MovieCharacter(values[0], values[1], values[2], values[3]);
            // Add movieCharacter object (line w/o ",") into Arraylist 
            characters.add(movieCharacter);
        }
        scanner.close(); 
    }
    
    /**
     * Adds a single MovieCharacter object to the characters ArrayList.
     *
     */
    public void addCharacter(MovieCharacter character) {
        characters.add(character);
    }

    /**
     * @return The number of characters in the movie.
     *
     */
    public int getNumberOfCharacters() {
        return characters.size();
    }

    @Override
    public String toString() {
    	StringBuilder result = new StringBuilder(name + "\n\n--------------- \n\n");
        for (MovieCharacter character : characters) {
            result.append(character.toString()).append("\n\n");
        }
        return result.toString();
    }
    
    // Getters and Setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRating() {
        return rating;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public ArrayList<MovieCharacter> getCharacters() {
        return characters;
    }

    public void setCharacters(ArrayList<MovieCharacter> characters) {
        this.characters = characters;
    }
}
