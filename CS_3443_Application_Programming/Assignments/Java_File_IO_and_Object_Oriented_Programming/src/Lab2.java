import java.io.IOException;

/**
 * Lab2 is a Java class containing a main method to run your program when completed.
 * This class will not compile until you have completed the requirements outlined in 
 * the lab description.
 * 
 * @author Mitra Hosseini (abc123)
 * UTSA CS 3443 - Lab 2
 * Fall 2023
 */
public class Lab2 {

	public static void main( String[] args ) {

		try {

			Movie barbies = new Movie( "Barbies" );
			barbies.loadCharacters( "barbies.csv" );
			System.out.println( barbies );

			Movie kens = new Movie( "Kens" );
			kens.loadCharacters( "kens.csv" );
			System.out.println( kens );

		}
		catch( IOException e ) {
			System.out.println( "Error loading the file - please check its location." );
			e.printStackTrace();
		}
	} 
}