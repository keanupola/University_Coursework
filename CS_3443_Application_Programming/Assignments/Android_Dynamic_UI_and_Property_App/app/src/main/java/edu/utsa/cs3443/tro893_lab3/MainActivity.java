package edu.utsa.cs3443.tro893_lab3;

import androidx.appcompat.app.AppCompatActivity;

import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;
import android.os.Bundle;


import edu.utsa.cs3443.tro893_lab3.model.Listing;
import edu.utsa.cs3443.tro893_lab3.model.Property;

/**
 * The main activity for this Property application.
 * It dynamically displays properties as buttons.
 *
 * @author Keanu Anderson-Pola
 * @abc123 tro893
 */
public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Listing listing;

    /**
     * Initializes listing and sets up property buttons.
     *
     * @param savedInstanceState, data most recently used or null
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Method calls
        createListing();
        dynamicSetupButtons();
    }

    /**
     * Displays property price or an error message if the property is not found.
     *
     * @param view, The button that was clicked
     */
    @Override
    public void onClick(View view) {
        // Cast the clicked view to a Button
        Button clickedButton = (Button) view;
        // Retrieve and convert address of clicked button to a string
        String address = clickedButton.getText().toString();

        // Find property details based on address
        Property property = listing.getProperty(address);

        if (property != null) {
            // Cast double to int for price
            Toast.makeText(view.getContext(), "$" + (int) property.getPrice(), Toast.LENGTH_LONG).show();
        } else {
            Toast.makeText(view.getContext(), "Property not found", Toast.LENGTH_LONG).show();
        }
    }

    /**
     * Dynamically generates and sets up buttons for each property.
     */
    private void dynamicSetupButtons() {
        // Create a layout object
        LinearLayout rootLayout = findViewById(R.id.root_layout);

        for (Property property : listing.getProperties()) {
            // For each property, create a button object
            Button propertyButton = new Button(this);
            propertyButton.setText(property.getLocation());
            propertyButton.setOnClickListener(this);
            // Setup the attributes for the button
            LinearLayout.LayoutParams buttonAttributes
                    = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT);
            // Add the button to the layout
            rootLayout.addView(propertyButton, buttonAttributes);
        }
    }

    /**
     * Initializes the property listing by loading properties from assets
     */
    private void createListing() {
        listing = new Listing();
        listing.loadProperties(this);
    }

}
