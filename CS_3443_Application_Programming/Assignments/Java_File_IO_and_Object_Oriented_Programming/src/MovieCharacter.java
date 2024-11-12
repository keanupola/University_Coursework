
/**
 * MovieCharacter is a class that represents the Ken and Barbie character in the Barbie movie with 
 * various attributes such as their character name/role in the movie, their actor's name, their gender and their duty.
 * 
 * @author Keanu Anderson-Pola
 */


public class MovieCharacter {

	private String characterName;  // ﻿"Everything Barbie"
    private String actorName;      // "Margot Robbie"
    private String gender;         // "Female"
    private String duty;           // "The real world explorer"

    // Constructors
    public MovieCharacter(String actorName, String characterName, String gender, String duty) {
        this.characterName = characterName;
        this.actorName = actorName;
        this.gender = gender;
        this.duty = duty;
    }
    // Without duty
    public MovieCharacter(String actorName, String characterName, String gender) {
    	// Using empty string as a placeholder for duty
        this(actorName, characterName, gender, "");  
    }

    @Override
    public String toString() {
        return "- " + characterName + "\n\n\tActor Name: " + actorName + "\n\n\tGender: " + gender + "\n\n\tDuty: " + duty;
    }

    // Getters and Setters
    public String getCharacterName() {
        return characterName;
    }

    public void setCharacterName(String characterName) {
        this.characterName = characterName;
    }

    public String getActorName() {
        return actorName;
    }

    public void setActorName(String actorName) {
        this.actorName = actorName;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getDuty() {
        return duty;
    }

    public void setDuty(String duty) {
        this.duty = duty;
    }
}

